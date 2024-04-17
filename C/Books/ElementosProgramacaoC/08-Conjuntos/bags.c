#include "bags.h"


int     Bagisin(Bagelem x, const Bag b)
{
    return b[x];
}

BagPtr  Bagunion(Bag b0, const Bag b1)
{
    for (Bagelem i = 0; i < BAG_DIM; i++)
        b0[i] += b1[i];
    return b0;
}

BagPtr  Baginter(Bag b0, const Bag b1)
{
    for (Bagelem i = 0; i < BAG_DIM; i++)
        if (b0[i] > b1[i])
            b0[i] = b1[i];
    return b0;
}

BagPtr  Bagdiff(Bag b0, const Bag b1)
{
    for (Bagelem i = 0; i < BAG_DIM; i++)
        b0[i] = b0[i] < b1[i] ? 0 : b0[i] - b1[i];
    return b0;
}

int     Bagissub(const Bag b0, const Bag b1)
{
    for (Bagelem i = 0; i < BAG_DIM; i++)
        if (b0[i] > b1[i])
            return 0;
    return 1;
}

size_t  Bagcard(const Bag b)
{
    size_t n = 0;
    for (Bagelem i = 0; i < BAG_DIM; i++)
        n += b[i];
    return n;
}

size_t  Bagcardu(const Bag b)
{
    size_t n = 0;
    for (Bagelem i = 0; i < BAG_DIM; i++)
        n += b[i] > 0;  // adds 1 or 0
    return n;
}

BagPtr  Bagclr(Bag b)
{
    for (Bagelem i = 0; i < BAG_DIM; i++)
        b[i] = 0;
    return b;
}

int     Bagisempty(const Bag b)
{
    for (Bagelem i = 0; i < BAG_DIM; i++)
        if (b[i])
            return 0;
    return 1;
}

int     Bagisequal(const Bag b0, const Bag b1)
{
    for (Bagelem i = 0; i < BAG_DIM; i++)
        if (b0[i] != b1[0])
            return 0;
    return 1;
}

BagPtr  Bagcpy(Bag b0, const Bag b1)
{
    for (Bagelem i = 0; i < BAG_DIM; i++)
        b0[i] = b1[i];
    return b0;
}

BagPtr  Bagadd(Bag b, Bagelem x)
{
    b[x]++;
    return b;
}

BagPtr  Bagrm(Bag b, Bagelem x)
{
    if (b[x])   // avoids integer overflow (unsigned bellow 0)
        b[x]--;
    return b;
}
