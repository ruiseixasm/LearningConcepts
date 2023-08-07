// Null Conditional Operator ?. is introduced in C# 6.0. It will return null if the left-hand side expression
// is evaluated to null instead of throwing an exception (NullReferenceException).  If the left-hand side expression
// evaluates to a nonnull value then it will be treated as a normal .(dot) operator and it might return null because
// its return type is always a nullable type means that for a struct or primitive type it is wrapped into a Nullable<T>.

using System;
using System.Collections.Generic;
using System.Linq;

public class Program
{
    public class Person {
        public string Name { get; set; } // Properties
        public Person Partner { get; set; }
        public string[] Hobbies { get; set; }
    }

    public NullReferenceError() { // This fails!
        Person person = null;
        Console.WriteLine(person.name);
    }

    public WithoutNullConditional() { // This works!
        Person person = null;
        if (person != null) {
            Console.WriteLine(person.name);
        }
    }

    public WithNullConditional() { // This works!
        Person person = null;
        Console.WriteLine(person?.name);
    }

    public static void Main() {
        // NullReferenceError(); // This fails! (has to be commented)
        WithoutNullConditional(); // This works!
        WithNullConditional(); // This works!
    }
}