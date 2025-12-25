# concurrency
Exploring concurrent programming.

Sample codes demo concurrency via async, multithreading and multiprocessing methods in:

* `py`: Python
* `cs`: C# / .NET

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


## Concurrency in C# / .NET

`/cs/ConsoleApp` provides a menu of different concurrency methods. Tasks print their unique IDs (0 - 9), also color coded for two concurrent tasks. The main method prints a heartbeat character (♥), allowing to recocognize the methods that don't block the main thread:

1. Independent I/O-bound tasks

![Independent I/O-bound](assets/cs-io.png)

2. Independent CPU-bound tasks

![Independent CPU-bound](assets/cs-cpu.png)

3. I/O-bound operations over a collection

![I/O-bound operations over a collection](assets/cs-io-collection.png)

4. CPU-bound operations over a collection

![CPU-bound operations over a collection](assets/cs-cpu-collection.png)