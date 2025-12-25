using System.Threading.Tasks;

public class Program
{
    // colors
    public const string Reset = "\x1b[0m";
    public const string Red = "\x1b[31m";
    public const string Green = "\x1b[32m";
    public const string Yellow = "\x1b[33m";
    public const string Blue = "\x1b[34m";
    
    // I/O-bound task
    public static async Task IoBoundTask(int id, string color)
    {                        
        Console.Write($"{color}[T{id} Started]{Reset}");
        // simulate the progress 
        for (int i = 0; i< 20; i++)
        {
            await Task.Delay(100);
            Console.Write($"{color}{id}{Reset}");            
        }
        Console.Write($"{color}[T{id} Done]{Reset}");        
    }

    // CPU-bound task
    public static void CpuBoundTask(int id, string color)
    {                        
        Console.Write($"{color}[T{id} Started]{Reset}");
        // simulate the progress 
        for (int i = 0; i< 1e9; i++)
        {
            if (i % 1e8 == 0)
            Console.Write($"{color}{id}{Reset}");            
        }
        Console.Write($"{color}[T{id} Done]{Reset}");        
    }

    // 1: Run Async
    public static async Task RunAsync()
    {
        var task1 =  IoBoundTask(1, Blue);
        await Task.Delay(1000); // to demo concurrency         
        var task2 =  IoBoundTask(2, Red);
        await Task.WhenAll(task1, task2); // wait for all to finish
        /* 
        Output:
        [T3 Started]330303[T4 Started]40430434034304034304[T3 Done]04040[T4 Done]
        */
        tasksDone = true;
    }

    // 2: Run Multithreading
    public static async Task RunMultithreading()
    {
        var task1 = Task.Run(()=> CpuBoundTask(3, Yellow));
        await Task.Delay(2000); // to demo concurrency
        var task2 = Task.Run(()=> CpuBoundTask(4, Green));
        await Task.WhenAll(task1, task2); // wait for all to finish
        /* Output:
        [T3 Started]330303[T4 Started]40430434034034034304[T3 Done]04040[T4 Done]
        */
        tasksDone = true;
    }

    // 3: Run parallell Async over a collection
    public static async Task RunAsyncCollection()
    {
        List<int> urlIds = Enumerable.Range(1, 10).ToList();
        await Parallel.ForEachAsync(urlIds, async (urlId, cancelationToken) =>
        {
            await IoBoundTask(urlId, Reset);
        });
        tasksDone = true;
    }

    // flag
    public static bool tasksDone = false;

    // main
    public static async Task<int> Main()
    {        
        // Operation mode arg
        ConsoleKeyInfo keyPress;
        while (true)
        {
            Console.WriteLine("\nPress a key: ");
            Console.WriteLine("1: Independent I/O-bound tasks");
            Console.WriteLine("2: Independent CPU-bound tasks");
            Console.WriteLine("3: I/O-bound operations over a collection");
            Console.WriteLine("4: CPU-bound operations over a collection");
            Console.WriteLine("q: Exit");
            keyPress = Console.ReadKey(true); // true: not displaying the key in the console

            if (keyPress.Key == ConsoleKey.Q)
            {
                return 1;
            }

            Console.Write($"{Green}[{keyPress.Key.ToString()[1]}] selected.");
            Console.WriteLine($" Tasks start shortly...");
            Console.WriteLine($"Press any key to exit\n{Reset}");
            Console.WriteLine("♥: Main's heartbeat\n");

            // Run tasks concurrently
            if (keyPress.Key == ConsoleKey.D1) 
            {
                // 1:
                var task = RunAsync();                
            }
            else if (keyPress.Key == ConsoleKey.D2)
            {
                // 2: 
                var task = RunMultithreading();            
            }            
            else if (keyPress.Key == ConsoleKey.D3)
            {
                // 3: 
                var task = RunAsyncCollection();
            }
            else
            {
                continue;
            }

            // This heartbeat shows up in the middle of the tasks
            // to show that the main thread is NOT blocked 
            while(!tasksDone)
            {
                Console.Write("♥");
                await Task.Delay(1000);
                if (Console.KeyAvailable) // exit on key pressed
                {
                    Console.WriteLine($"\n{Red}User exited{Reset}"); 
                    return 1;
                }
            }           
            Console.WriteLine("\n\nTasks done\n"); 
            return 0;

        }
    }
}