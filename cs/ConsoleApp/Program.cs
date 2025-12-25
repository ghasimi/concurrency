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

    // Run Async
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
    }

    // Run Multithreading
    public static async Task RunMultithreading()
    {
        var task1 = Task.Run(()=> CpuBoundTask(3, Yellow));
        await Task.Delay(2000); // to demo concurrency
        var task2 = Task.Run(()=> CpuBoundTask(4, Green));
        await Task.WhenAll(task1, task2); // wait for all to finish
        /* Output:
        [T3 Started]330303[T4 Started]40430434034034034304[T3 Done]04040[T4 Done]
        */
    }

    // main
    public static async Task Main()
    {
          
        Console.WriteLine($"\nTasks start shortly...");
        Console.WriteLine($"{Green}Press any key to exit\n{Reset}");
        Console.WriteLine("♥: Main's heartbeat");

        // Run tasks concurrently
        var ioTasks = RunAsync();                
        var cpuTasks = RunMultithreading();

        // This heartbeat shows up in the middle of the tasks
        // to show that the main thread is NOT blocked 
        while(true)
        {
            Console.Write("♥");
            await Task.Delay(1000);
            if (Console.KeyAvailable) // exit on key pressed
            {
                break;
            }
        }

        /*
        Output:
        [T1 Started]♥[T3 Started]31111131111[T2 Started]♥121213212121212121321♥[T4 Started]421[T1 Done]22222423222♥2[T2 Done]434♥343♥43♥434♥[T3 Done]♥♥♥♥♥♥
        */
        Console.WriteLine("\n\nTasks finished\n"); 
    }
}