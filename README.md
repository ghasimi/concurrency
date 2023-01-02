# concurrency
Exploring concurrent programming.

## Concurrency in Python

`sample_thread.py` allows testing _multithreading_ and _multiprocessing_ for different tasks, including I/O-bound and CPU-bound. 

### Example: CPU-Bound Tasks

The following tests demonstrates that for CPU-bound tasks in Python, _multithreading_ doesn't help, while  _multiprocessing_ helps. 

1. CPU-Bound, Sequential: ~15s (benchmark)

![CPU-bound, Sequential](cpu-sequential.png)

2. CPU-Bound, Multithreading: ~15s (no gain) 

![CPU-bound, Multithreading](cpu-multithreading.png)

3. CPU-Bound, Multiprocessing: ~5s (huge gain) 

![CPU-bound, Multiprocessing](cpu-multiprocessing.png)
