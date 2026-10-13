# In-Memory Concurrent Task Runner

#### The Problem Statement

You have an application where client tasks arrive unpredictably. If you run them sequentially, slow tasks block fast tasks. If you spawn a new OS thread for every single task, your program consumes gigabytes of stack memory and collapses under context-switching thrashing.

We need an in-process engine that keeps a **fixed pool of worker threads** alive, accepts arbitrary tasks, and executes them concurrently.

---

### Functional Requirements

1. **Bounded / Safe Task Storage:**

- A thread-safe holding area where tasks can be submitted and held in memory.
- Multiple worker threads will pull from this area concurrently without corrupting it.
- If the holding area is empty, workers must **not** spin-loop; they must sleep at 0% CPU.

2. **The Worker Pool:**

- Allocates a fixed number of worker threads (e.g., matching hardware concurrency).
- Workers run an event loop: sleep until a task is available $\rightarrow$ wake up $\rightarrow$ execute task $\rightarrow$ go back to sleep.

3. **Task Return Tracking:**

- When someone submits a job that produces a result (e.g., computing a hash or a sum), they must receive a ticket/handle that lets them retrieve that result whenever the worker finishes computing it.

4. **Telemetry & Metrics:**

- Track the total number of completed tasks and running metrics across all threads **without using any mutex locks** for the counters.

5. **Graceful Teardown:**

- When the engine stops, it must drain pending tasks, wake up every sleeping worker, and terminate all threads cleanly without crashing or leaving dangling threads.
