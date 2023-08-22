using System;

namespace Generics;

public class CompareClass
{
    static void Main(string[] args)
    {
        int i1 = 2;
        int i2 = 2;

        float f1 = 2.0f;
        float f2 = 2.0f;

        Compare<int>(i1, i2); // have to specifie the type
        Compare<float>(f1, f2); // have to specifie the type
        Compare(i1, f2); // Implicit type inference

        Console.ReadKey();
    }

    private static void Compare<T>(T i1, T i2)
    {
        Console.WriteLine("Same data type!");
    }

    private static void Compare<T1, T2>(T1 i1, T2 i2) // where T1 != T2
    {
        Console.WriteLine("Different data type!");
    }
}
