#include <stdio.h>
#include <stdarg.h>

void common_function(int first_arg, int second_arg)
{
    printf("First: %d and second: %d\n", first_arg, second_arg);
}

void stdarg_function(int total_args, ...)
{
    va_list p;
    va_start(p, total_args); // Expects 2 args in this particular case (while total_args--)
    int first_arg = va_arg(p, int);
    int second_arg = va_arg(p, int);
    printf("First: %d and second: %d\n", first_arg, second_arg);
}

int main()
{
    int x = 7;
    common_function(x, x++);

    int y = 7;
    stdarg_function(2, y, y++);

    return 0;
}