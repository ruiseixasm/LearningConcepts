// ref is used to state that the parameter passed may be modified by the method.
// out is used to state that the parameter passed must be modified by the method.
// in is used to state that the parameter passed cannot be modified by the method.

Main(); // Needs to call the Main() function

void Main ()
{
    int value = 0;

    CallByReference(ref value);
    Console.WriteLine($"The value is: {value}");

    CallByOut(out value);
    Console.WriteLine($"The value is: {value}");

    CallByIn(in value); // in not mandatory
}

void CallByReference(ref int variable)
{
    // Has NO NEED to change the ref variable despite being allowed to
}

void CallByOut (out int variable)
{
    variable = 33; // Has to change the out variable mandatorily
}

void CallByIn(in int variable)
{
    //variable = 33; // Cannot change the out variable
    Console.WriteLine($"The value is: {variable}");
    Console.WriteLine($"The value type is: {variable.GetType}");
}