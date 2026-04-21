*This project has been created as part of the 42 curriculum by jsam.*

# Codexion

## Description

**Codexion** is a multithreaded simulation project inspired by the classic *Dining Philosophers* problem.
In this version, "coders" compete for shared resources called *dongles* in order to perform tasks such as compiling, debugging, and refactoring.

The goal of the project is to explore **concurrency, synchronization, and scheduling strategies**, while ensuring that all threads operate safely without deadlocks, starvation, or race conditions.

Each coder follows a cycle:

1. Take two dongles
2. Compile
3. Debug
4. Refactor

The simulation stops when:

* A coder **burns out** (fails to compile within a given time),
* Or all coders have completed the required number of compilations.

---

## Instructions

### Compilation

Use the provided Makefile:

```bash
make
```

For debugging with thread sanitizer:

```bash
make debug
```

### Usage

```bash
./codexion n_coders t_burnout t_compile t_debug t_refactor n_compiles t_cooldown scheduler
```

### Arguments

* `n_coders` → Number of coders (must be > 1)
* `t_burnout` → Time before a coder burns out (ms)
* `t_compile` → Time spent compiling (ms)
* `t_debug` → Time spent debugging (ms)
* `t_refactor` → Time spent refactoring (ms)
* `n_compiles` → Number of compilations required per coder
* `t_cooldown` → Cooldown time for dongles after use (ms)
* `scheduler` → Scheduling strategy:

  * `fifo` (First-In, First-Out)
  * `edf` (Earliest Deadline First)

### Example

```bash
./codexion 5 800 200 100 100 3 50 fifo
```

---

## Blocking Cases Handled

This project addresses several classic concurrency issues:

### Deadlock Prevention

Deadlocks are prevented by:

* Enforcing a **strict resource ordering** (each coder always locks dongles in the same order).
* Using a **priority-based access system** via request queues.

This breaks Coffman’s circular wait condition.

---

### Starvation Prevention

Each dongle maintains a **priority queue (min-heap)** of requests:

* In `fifo`, priority is based on request time.
* In `edf`, priority is based on last compile time.

This ensures fair access and prevents threads from being indefinitely delayed.

---

### Cooldown Handling

After use, each dongle enters a **cooldown period**:

* Prevents immediate reuse
* Forces fair distribution of resources
* Managed using timestamps and monitored globally

---

### Burnout Detection

A dedicated monitor thread continuously checks:

* If a coder has exceeded `t_burnout` since last compile

If so:

* The simulation stops immediately
* A "burned out" message is printed

---

### Log Serialization

All output is protected by a **mutex (`mutex_print`)**:

* Prevents interleaved or corrupted logs
* Ensures consistent and readable output

---

## Thread Synchronization Mechanisms

This project relies on several threading primitives:

### Mutexes (`pthread_mutex_t`)

Used to protect shared data:

* `mutex_print` → logging
* `mutex_state_sim` → simulation state (start/stop)
* `mutex_state_dongles` → dongle availability and queues
* `mutex_coder` → per-coder data
* `mutex_dongle` → individual resource locking

These ensure **mutual exclusion** and prevent race conditions.

---

### Condition Variables (`pthread_cond_t`)

Used for efficient thread coordination:

* `cond_start` → synchronizes simulation start
* `cond_state_dongles` → signals resource availability changes

Threads wait instead of busy-waiting, improving performance and correctness.

---

### Thread Coordination Strategy

* Coders **register requests** in both dongles' queues.
* They wait until:

  * Both dongles are available
  * They have **priority** on both queues
  * Cooldown has expired

Only then can they proceed.

---

### Race Condition Prevention

Race conditions are avoided by:

* Always locking shared state before access
* Using condition variables instead of polling
* Separating resource state (availability) from actual locking (mutex)

---

### Thread-safe Communication

* Shared state is always accessed under mutex protection
* Condition variables ensure safe signaling between:

  * Coders
  * Monitor thread

---

## Resources

### Documentation

* POSIX Threads (pthreads) documentation
* "The Dining Philosophers Problem" (classic concurrency problem)
* Operating Systems course materials (thread synchronization & scheduling)

---

### AI Usage

AI tools were used in this project for:

* Understanding concurrency patterns and edge cases
* Clarifying pthread behaviors and synchronization strategies
* Assisting with documentation (README structure and clarity)

All design decisions, implementation, and debugging were done manually.

---

## Additional Notes

* The project includes a **monitor thread** to supervise the simulation.
* A **custom priority queue (heap)** is used for scheduling access to resources.
* The implementation supports multiple scheduling strategies (`fifo` and `edf`).

---

## Author

* jsam (42 Lyon)