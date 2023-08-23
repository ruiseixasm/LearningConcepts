using System;

namespace Variance; // Covariance and Contravariance are two forms of Variance

public class Animal { }

public class Cat : Animal { } // Cat is a subtype of Animal

public class Program
{
    public static Animal CovariantMethod ()
    {
        Console.WriteLine("Covariance!");
        return new Cat ();
    }

    public static void ContravariantMethod(Animal animal)
    {
        Console.WriteLine("Contravariance!");
    }

    static void Main(string[] args)
    {

        CovariantMethod(); // Covariance
        ContravariantMethod(new Cat()); // Contravariance

        Console.ReadKey();
    }
}
