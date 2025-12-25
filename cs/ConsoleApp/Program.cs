using System.Threading.Tasks;

public class Program
{
    // colors
    public const string Reset = "\x1b[0m";
    public const string Red = "\x1b[31m";
    public const string Green = "\x1b[32m";
    public const string Yellow = "\x1b[33m";
    public const string Blue = "\x1b[34m";
    
    // task
    public static async Task DoAsync(int id, string color)
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

    // main
    public static async Task Main()
    {
        Console.WriteLine($"\nTasks start shortly...\n");
        var task1 =  DoAsync(1, Blue);
        await Task.Delay(1000); // to demo concurrency         
        var task2 =  DoAsync(2, Red);
        await Task.WhenAll(task1, task2); // wait for all to finish
        /* 
        Output:
        [T1 Started]111111111[T2 Started]121212121212121212121[T1 Done]2222222222[T2 Done]
        */
        Console.WriteLine("\n\nTasks finished\n"); 
    }
}