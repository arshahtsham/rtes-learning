# Producer-Consumer Problem using Mutex and Semaphores (C / Pthreads)

## Overview

This program demonstrates the classic **Producer-Consumer problem** using:

* **Multiple producer threads**
* **Multiple consumer threads**
* A **shared buffer**
* **Mutex** for mutual exclusion
* **Semaphores** for synchronization

The goal is to allow producers and consumers to operate at **different rates** without causing:

* Buffer **overflow** (producer writing when full)
* Buffer **underflow** (consumer reading when empty)
* **Race conditions** on shared data

---

## Key Concepts

### 1. Shared Buffer

```c
int buffer[10];
int count = 0;
```

* `buffer` stores produced items
* `count` tracks the number of items currently in the buffer

---

### 2. Mutex (Mutual Exclusion)

```c
pthread_mutex_t mutexBuffer;
```

Used to protect the **critical section**:

```c
pthread_mutex_lock(&mutexBuffer);
// access buffer and count
pthread_mutex_unlock(&mutexBuffer);
```

Why?

* Producers and consumers both modify `count` and `buffer`
* Without mutex → **race condition**
* Mutex ensures **only one thread accesses shared data at a time**

---

### 3. The Problem Without Semaphores

Even with mutex, we still have logical issues:

* Producer may write when buffer is **full** → overflow
* Consumer may read when buffer is **empty** → underflow

Using simple `if` checks is not ideal because:

* Threads would keep checking → **busy waiting (CPU waste)**
* Timing issues can still cause incorrect behavior

---

## 4. Semaphores Solution

We use **two semaphores**:

```c
sem_t semEmpty;  // tracks empty slots
sem_t semFull;   // tracks filled slots
```

### Initial Values

```c
sem_init(&semEmpty, 0, 10);  // buffer size
sem_init(&semFull, 0, 0);    // initially empty
```

---

## 5. Producer Logic

```c
sem_wait(&semEmpty);   // reserve an empty slot

pthread_mutex_lock(&mutexBuffer);
buffer[count] = x;
count++;
pthread_mutex_unlock(&mutexBuffer);

sem_post(&semFull);    // signal that a new item is available
```

### Meaning

* **Before producing** → ensure space exists
* **After producing** → notify consumers that data is available

---

## 6. Consumer Logic

```c
sem_wait(&semFull);    // wait for available data

pthread_mutex_lock(&mutexBuffer);
y = buffer[count - 1];
count--;
pthread_mutex_unlock(&mutexBuffer);

sem_post(&semEmpty);   // signal that space is now available
```

### Meaning

* **Before consuming** → ensure data exists
* **After consuming** → notify producers that space is free

---

## 7. Intuition (Important)

Think of the buffer like a **tank with two sensors**:

| Condition              | Semaphore  | Purpose           |
| ---------------------- | ---------- | ----------------- |
| Empty slots available  | `semEmpty` | Controls producer |
| Filled slots available | `semFull`  | Controls consumer |

### Key Rule

```
Producer: empty → full
Consumer: full → empty
```

---

## 8. Why Two Semaphores?

We must handle **two independent conditions**:

1. Buffer is **not full** → producer can write
2. Buffer is **not empty** → consumer can read

A single semaphore can only represent **one condition**, so we need two.

---

## 9. Final Behavior

* Producers and consumers can run at **different speeds**
* Threads will **block automatically** when needed:

  * Producer blocks when buffer is full
  * Consumer blocks when buffer is empty
* No:

  * Overflow
  * Underflow
  * Busy waiting

---

## 10. Summary

* **Mutex** → protects shared data (correctness)
* **Semaphores** → control execution flow (synchronization)

Together, they ensure a safe and efficient producer-consumer system.

---
