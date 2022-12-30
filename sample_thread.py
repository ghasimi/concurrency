import threading
import multiprocessing
from concurrent.futures import ThreadPoolExecutor
import logging
import time
import math
from urllib.request import urlopen

logging.basicConfig(
    level=logging.DEBUG,
    datefmt='%Y-%m-%d %H:%M:%S',
    format='%(asctime)s.%(msecs)03d %(levelname)s %(module)s - %(funcName)s: %(message)s',
)

N = int(3e8)

def compute(n=N):
    for i in range(1,n):
        _ = math.log(i)

def getWebpage(url='https://download.bls.gov/pub/time.series/cu/cu.data.0.Current'):
    return urlopen(url).read()

def long_running_func(_id=0, task_type=1, n=N):

    if task_type == 1:
        logging.info(f'Task {_id}: started I/O-bound...' )
        _ = getWebpage()

    if task_type == 2:
        logging.info(f'Task {_id}: started CPU-bound...' )
        compute(n)

    if task_type == 3:
        logging.info(f'Task {_id}: started Sleep...' )
        time.sleep(3)
    
    logging.info(f'Task {_id}: finished' )
        
if __name__ == '__main__':
    print('\n')
    
    MODES = {
        1:'Sequentional', 
        2:'Multithreading', 
        3:'Multithreading with ThreadPoolExecuter', 
        4:'Multiprocessing',
    }

    task_type = input(f'Enter task type #: 1: I/O-bound,  2: CPU-bound, 3: Sleep: ')
    task_type = int(task_type)

    print('Modes list:')
    for mode in MODES:
        print(f'{mode}: {MODES[mode]}')

    mode = input('Enter mode # to try: ')
    mode = int(mode)

    logging.info(f'Mode: {MODES[mode]}')
    logging.info(f'Before threads')
    
    # args the tasks
    args = [
        (1, task_type, N//3),
        (2, task_type, N//3),
        (3, task_type, N//3),
    ] 

    threads = []

    startTime = time.time()

    # Sequentional
    if mode == 1:
        for arg in args:
            long_running_func(*arg)
    
    # Multithreading
    if mode == 2:
        for arg in args:
            t = threading.Thread(target=long_running_func, args=arg, daemon=False)                    
            t.start()
            threads.append(t)

        for t in threads:
            t.join()
    
    # Multithreading with ThreadPoolExecutor
    if mode == 3:
        executer = ThreadPoolExecutor(max_workers=len(args))
        for res in executer.map(lambda p: long_running_func(*p), args):
            pass

    # Multiprocessing
    if mode == 4:
        p = multiprocessing.Pool(len(args))
        xs = p.starmap(long_running_func, args)

    totTime = time.time() - startTime

    logging.info(f'After threads. Done in {totTime:.06f}s')
    
    print('\n')
