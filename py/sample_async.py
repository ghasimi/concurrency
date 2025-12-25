import asyncio 
import random 

def add_color(msg, color='\033[0m'):
    return  f'{color}{msg}\033[0m'

class Task():
    def __init__(self, _id=0):
        self._id = _id       
        self.color = f'\033[3{_id+1}m'

    async def start(self,):
        x = random.randrange(1,10)
        print(add_color(f'Task #{self._id}: started...', self.color))
        await asyncio.sleep(x)
        print(add_color(f'Task #{self._id}: finished in {x}s', self.color))

    def __repr__(self):
        return add_color(f'Task #{self._id}\033[0m', self.color)
    

async def task_executer(_id=0):
    task = Task(_id)
    await task.start()
    return task

async def main():
    res = await asyncio.gather(*[task_executer(i) for i in range(5)])
    return res

random.seed(1)

res = asyncio.run(main())
