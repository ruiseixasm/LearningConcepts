// Compile command: gcc 04-primes-eratosthenes.c sets.c -DSET_MAX=65535 -o 04-primes-eratosthenes.out

// Eratosthenes of Cyrene - Primes

#include "sets.h"

SetPtr primes_sieve_full(Set primes, int lim)
{
    Set sieve;
    int next = 2;                       // starts at 2
    int multiple;
    Setaddrng(Setclr(sieve), 2, lim);   // size of lim - 1
    Setadd(Setclr(primes), 1);          // 1 is prime
    
    do
    {
        while (!Setisin(next, sieve))
            next++;
        Setadd(primes, next);
        for (multiple = next; multiple <= lim; multiple += next)
            Setrm(sieve, multiple);
    } while (!Setisempty(sieve));
    
    return primes;    
}

SetPtr primes_sieve(Set primes, int lim)
{
    Set sieve;
    int next = 2;
    int multiple;
    Setaddrng(Setclr(sieve), 2, lim);
    Setadd(Setclr(primes), 1);          // 1 is prime
    
    do
    {
        while (!Setisin(next, sieve))
            next++;
        Setadd(primes, next);
        for (multiple = next; multiple <= lim; multiple += next)
            Setrm(sieve, multiple);
    } while (next*next < lim);
    
    return Setunion(primes, sieve);     // | (or) bitwise operator   
}

SetPtr primes_neat(Set primes, int lim)
{
    int next = 1;
    int multiple;
    Setaddrng(Setclr(primes), 1, lim);
    
    do
    {
        do next++;      // starts at 2
        while (!Setisin(next, primes));
        for (multiple = next*next; multiple <= lim; multiple += next)
            Setrm(primes, multiple);
    } while (next*next < lim);
    
    return primes;
}

int main()
{
    Set primes;
    int top = 100;  // top maximum prime
    
    printf("A: ");
    primes_sieve_full(primes, top);
    Setprint(primes, NULL, 0, 0);
    
    printf("\nB: ");
    primes_sieve(primes, top);
    Setprint(primes, NULL, 0, 0);
    
    printf("\nC: ");
    primes_neat(primes, top);
    Setprint(primes, NULL, 0, 0);
    
    printf("\n");
    
    return 0;
}
