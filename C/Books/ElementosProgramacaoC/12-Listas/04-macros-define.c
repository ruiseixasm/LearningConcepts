// Compile command: gcc 04-macros-define.c -o 04-macros-define.out
#include <math.h>
#include <stdio.h>

#define cubrt(x) pow(x, 0.3333333)
#define up3(x) x + 3    // 2*up3(5) is equal to 13 and not 16!
#define up4(x) (x + 4)  // 2*up4(5) is correctly equal to 18
#define cube(x) (x * x * x)

#define listnull(s) (!s)
#define listhead(s) (s->value)
#define listtail(s) (s->next)

int main()
{
    printf("cube(3) = %d\n", cube(3));  // cube(3) = 27

    return 0;
}