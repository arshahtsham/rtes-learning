### Semaphore Example using POSIX Threads in C

#### Overview

This program demonstrates a basic use of a **semaphore** to control concurrency among multiple threads using POSIX threads (`pthread`).

---

#### What the Program Does

* Creates **4 threads**
* Each thread runs a routine that:

  * Waits on a semaphore
  * Prints a message
  * Releases the semaphore

---

#### Without Semaphore

If no semaphore is used:

* All threads can execute concurrently
* The order of execution is **unpredictable**

---

#### With Semaphore

```c
sem_init(&semaphore, 0, 2);
```

* The semaphore is initialized with a value of **2**
* This means:
  → **Only 2 threads can execute the critical section at the same time**

---

#### Key Concepts

##### 1. `sem_wait()`

* Decrements the semaphore value
* If the value is **0**, the thread **blocks (waits)**

##### 2. `sem_post()`

* Increments the semaphore value
* Wakes up waiting threads

---

#### Execution Flow

1. Initially:

   ```
   semaphore = 2
   ```

2. First two threads:

   * Call `sem_wait()` → allowed to run
   * Semaphore becomes `0`

3. Remaining threads:

   * Block at `sem_wait()`

4. When running threads call `sem_post()`:

   * Semaphore increases
   * Waiting threads are allowed to proceed

---

#### Important Detail: Passing Thread Arguments

```c
int* a = malloc(sizeof(int));
*a = i;
pthread_create(&th[i], NULL, routine, a);
```

* Each thread receives a **separate memory location**
* This stores a copy of `i`

Why this is necessary:

* The loop variable `i` is shared and keeps changing
* Passing `&i` would result in incorrect values across threads
* Using `malloc` ensures each thread gets the correct value

---

#### Summary

* Semaphore controls **how many threads run simultaneously**
* Here, only **2 threads run in parallel**
* Threads beyond that **wait until resources are available**
* Dynamic allocation ensures **correct thread-specific data**

---

#### Output Behavior

Output order may vary, but:

* Only **2 threads print at the same time**
* Others wait until the semaphore is released

---

#### Cleanup

```c
sem_destroy(&semaphore);
```

* Frees resources associated with the semaphore
