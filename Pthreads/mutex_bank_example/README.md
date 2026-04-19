# Mutex Bank Example (Race Condition)

## What this program does

Two threads perform deposits on a shared bank account balance:

* Thread 1 deposits 300
* Thread 2 deposits 200

Both threads run concurrently.

---

## Problem (without mutex)

The deposit operation is **not atomic**. It consists of:

1. Read current balance
2. Add deposit amount
3. Write updated balance

This is called a **read-modify-write cycle**.

Because both threads run at the same time, this can happen:

* Thread 1 reads balance = 1000
* Thread 2 also reads balance = 1000
* Thread 1 writes 1300
* Thread 2 writes 1200

Final balance becomes **1200 instead of 1500**

👉 This is a **race condition**

---

## Why this happens

Both threads access the shared variable (`balance`) **without synchronization**, so their operations overlap.

The inserted delay increases the chance of this overlap.

---

## Solution (using mutex)

A mutex is used to protect the **critical section**:

```c
pthread_mutex_lock(&mutex);

// read + modify + write

pthread_mutex_unlock(&mutex);
```
Thread 2 must not read the shared balance until Thread 1 completes its whole critical section
that is: read → modify → write

This ensures:

* Only one thread accesses the balance at a time
* The operation becomes effectively **atomic**

---

## Key Learning

* Race conditions occur when multiple threads access shared data without synchronization
* Read-modify-write operations are especially vulnerable
* Mutex ensures mutual exclusion and correct results

---

## Expected Behavior

* Without mutex → incorrect final balance (non-deterministic)
* With mutex → correct final balance (deterministic)

https://www.youtube.com/watch?v=raLCgPK-Igc
