using System.Diagnostics;

public static class Program
{
    public static void Part1()
    {
        var lines = File.ReadAllLines("input.txt");
        var times = lines[0].Split(' ', StringSplitOptions.RemoveEmptyEntries);
        var distances = lines[1].Split(' ', StringSplitOptions.RemoveEmptyEntries);
        
        List<int> values = new();
        for (var race = 0; race < times.Length - 1; race++)
        {
            var time = Convert.ToInt32(times[race + 1]);
            var minimumDistance = Convert.ToInt32(distances[race + 1]);

            var hasWonYet = false;
            var wins = 0;
            for (var i = 1; i < time; i++)
            {
                if ((time - i) * i > minimumDistance)
                {
                    wins++;
                    hasWonYet = true;
                }
                else
                {
                    if (!hasWonYet) continue;
                    values.Add(wins);
                    break;
                }
            }
        }

        var sum = values.Aggregate(1, (current, val) => current * val);
        Console.WriteLine($"Part 1: {sum}");
    }
    
    public static void Part2()
    {
        var lines = File.ReadAllLines("input.txt");
        var times = lines[0].Split(' ', StringSplitOptions.RemoveEmptyEntries).ToList();
        var distances = lines[1].Split(' ', StringSplitOptions.RemoveEmptyEntries).ToList();
        times.RemoveAt(0);
        distances.RemoveAt(0);

        // Day 2
        times = new List<string>(new[]{times.Aggregate("", (source, token) => source + token)});
        distances = new List<string>(new[]{distances.Aggregate("", (source, token) => source + token)});
        
        List<int> values = new();
        for (var race = 0; race < times.Count; race++)
        {
            var time = Convert.ToUInt64(times[race]);
            var minimumDistance = Convert.ToUInt64(distances[race]);

            var hasWonYet = false;
            var wins = 0;
            for (ulong i = 1; i < time; i++)
            {
                if ((time - i) * i > minimumDistance)
                {
                    wins++;
                    hasWonYet = true;
                }
                else
                {
                    if (!hasWonYet) continue;
                    values.Add(wins);
                    break;
                }
            }
        }

        Console.WriteLine($"Part 2: {values[0]}");
    }

    public static void Main(string[] args)
    {
        Stopwatch sw = new();
        sw.Start();
        Part1();
        sw.Stop();
        Console.WriteLine($"Completed Part 1 in {sw.ElapsedMilliseconds}ms");
        sw.Restart();
        Part2();
        sw.Stop();
        Console.WriteLine($"Completed Part 2 in {sw.ElapsedMilliseconds}ms");
    }
}
