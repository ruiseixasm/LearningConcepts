
long long int calc_sum_c(int n) {
    long long int sum = 0;
    for (int i = 0; i < n; ++i)
        sum += i;
    return sum;
}


// Generate the .so file with this command
// gcc test4.c -shared -o test4.so -fPIC
