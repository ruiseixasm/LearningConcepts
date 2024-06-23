#include <stdio.h>

void common_function(int first_arg, int second_arg)
{
    printf("First: %d and second: %d\n", first_arg, second_arg);
}

int main()
{
    int x = 7;
    common_function(x, x++);
    x = 7;
    common_function(x++, x);

    return 0;
}

/*

In C, the order of evaluation for function arguments is unspecified, which means it can vary depending on the compiler
    and its optimization settings. Even though some compilers might often evaluate arguments from right to left,
    this is not guaranteed by the C standard, and thus can lead to different behaviors in different contexts.

### Explanation of the Example

Given the two calls:

1. `common_function(x, x++);`
2. `common_function(x++, x);`

### Analysis of `common_function(x, x++)`

Let's consider this step by step:

- `x` is initialized to `7`.
- `common_function(x, x++);`

#### Typical Right-to-Left Evaluation:

- **Step 1:** Evaluate `x++`:
  - Current value of `x` is `7`, so `x++` evaluates to `7`.
  - After the evaluation, `x` is incremented to `8`.

- **Step 2:** Evaluate `x`:
  - Now `x` is `8`.

So, the arguments passed to `common_function` would be `(8, 7)`.

### Analysis of `common_function(x++, x)`

Now let's consider this step by step:

- `x` is initialized to `7`.
- `common_function(x++, x);`

#### Typical Right-to-Left Evaluation:

- **Step 1:** Evaluate `x`:
  - Current value of `x` is `7`.

- **Step 2:** Evaluate `x++`:
  - Current value of `x` is `7`, so `x++` evaluates to `7`.
  - After the evaluation, `x` is incremented to `8`.

So, the arguments passed to `common_function` would be `(7, 8)`.

### Conclusion

The observed behavior aligns with the idea that the order of evaluation is unspecified and can lead to different results:

- For `common_function(x, x++)`, the arguments are `(8, 7)`, leading to the output:
  ```
  First: 8 and second: 7
  ```

- For `common_function(x++, x)`, the arguments are `(7, 8)`, leading to the output:
  ```
  First: 7 and second: 8
  ```

### Important Points

- **Unspecified Evaluation Order:** The C standard leaves the order of evaluation of function arguments unspecified,
    which can lead to different results in different contexts or compilers.
- **Compiler Behavior:** The behavior you observe can be influenced by compiler optimizations and specific implementation details.
    It is important not to rely on any particular order of evaluation in portable code.

To avoid such issues and ensure predictable behavior, it is best to avoid writing code that depends on the order of evaluation
    of function arguments. You can use temporary variables to make the order of operations explicit:

```c
    #include <stdio.h>

    void common_function(int first_arg, int second_arg)
    {
        printf("First: %d and second: %d\n", first_arg, second_arg);
    }

    int main()
    {
        int x = 7;
        int first = x;
        int second = x++;
        common_function(first, second);

        x = 7;
        first = x++;
        second = x;
        common_function(first, second);

        return 0;
    }
```

This ensures that the evaluation order is explicit and avoids reliance on unspecified behavior.

*/
