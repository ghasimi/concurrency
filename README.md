# concurrency
Exploring concurrent programming.

## Concurrency in Python

### I. Multithreading and Multiprocessing

`py/sample_thread.py` allows testing _multithreading_ and _multiprocessing_ for different tasks, including I/O-bound and CPU-bound. 

#### Example: CPU-Bound Tasks

The following tests demonstrates that for CPU-bound tasks in Python, _multithreading_ doesn't help, while  _multiprocessing_ helps. 

1. CPU-Bound, Sequential: ~15s (benchmark)

![CPU-bound, Sequential](assets/py-cpu-sequential.png)

2. CPU-Bound, Multithreading: ~15s (no gain) 

![CPU-bound, Multithreading](assets/py-cpu-multithreading.png)

3. CPU-Bound, Multiprocessing: ~5s (huge gain) 

![CPU-bound, Multiprocessing](assets/py-cpu-multiprocessing.png)

### II. Asynchronous I/O

`py/sample_async.py` leverages Python's [asyncio](https://docs.python.org/3/library/asyncio.html).

<img alt="Async I/O" src="assets/py-async.png" width="500" /> 