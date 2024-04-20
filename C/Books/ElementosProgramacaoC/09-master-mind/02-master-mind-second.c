// Compile command: gcc 02-master-mind-second.c random.c sets.c bags.c input.c -DSET_MAX=59048 -o 02-master-mind-second.out

#include <stdio.h>
#include <string.h>
#include <stddef.h>     // for size_t
#include "random.h"
#include "sets.h"
#include "bags.h"
#include "input.h"

#define POSITIONS       4               // Not used!    -
#define COLOURS         6               // Not used!    -
#define LOW_COLOUR      '1'             // Used         +
#define HIGH_COLOUR     '0' + COLOURS   // Not used!    -

#define MIN_POSITIONS   4
#define MAX_POSITIONS   5
#define MIN_COLOURS     6
#define MAX_COLOURS     9

int positions   = MIN_POSITIONS;
int colours     = MIN_COLOURS;

                             // + 1 to allow '\0' at the end (avoids memory leak!)
typedef char Perm[MAX_POSITIONS + 1];   // global variable that by default all elements are 0

// 1st PART of the master mind game (primeiro subproblema)

long ipow(int x, int n)     // same as <math.h> pow() but for int/long instead of double
{
    long p = 1;     // for n = 0 it must return 1
    while (n--)
        p *= x;
    return p;
}

int btwn(int x, int a, int b)
{
    return x < a ? a : x > b ? b : x;    
}

int setpositions(int n)
{
    return positions = btwn(n, MIN_POSITIONS, MAX_POSITIONS);    
}

int setcolours(int n)
{
    return colours = btwn(n, MIN_COLOURS, MAX_COLOURS);    
}

int isPerm(const char *s)
{
    int i = 0;
    for ( ; s[i] > 0; i++)       // vs: HIGH_COLOUR
        if (s[i] < LOW_COLOUR || s[i] > LOW_COLOUR + colours)
            return 0;
    return i == positions;
}

int strmtch(const char *s, const char *t)
{
    int n = 0;
    for (int i = 0; s[i] && t[i]; i++)
        n += s[i] == t[i];
    return n;
}

int strcmmn(const char *s, const char *t)
{
    // Bags of colours
    Bag bs;
    Bag bt;
    Bagclr(bs);
    Bagclr(bt);
    
    // loop working as Bagaddstr
    for (int i = 0; s[i] && t[i]; i++)
    {
        Bagadd(bs, s[i]);
        Bagadd(bt, t[i]);
    }
    
    // returns the common amount of colours (inter: min of two bags)
    // Baginter(bs, bt);
    // int common = Bagcard(bs);
    // return common;
    return Bagcard(Baginter(bs, bt));
}

int Permcmp(const Perm p1, const Perm p2, int *black, int *white)
{
    // black: perfect match
    // white: colour match only
    *white = strcmmn(p1, p2) - (*black = strmtch(p1, p2));  // complementary that are just common
    return *black == positions; // Check is all colours match that means won
}

char* strrand(char s[], int n, char c0, char c1,
                    char (*r) (char, char))  // function signature. (*) is the pointer to function r
{
    char *s0 = s;   // s already a pointer, no need for &s
    while (n--)
        *s++ = r(c0, c1);
    *s = '\0';      // same as 0, the reason why Perm[MAX_POSITIONS + 1] (+ 1)
    return s0;
}

char crandrng(char c0, char c1)
{
    return iRandomrng(c0, c1);
}

char* Permfunc(Perm p, char (*f) (char, char))
{
    return strrand(p, positions, LOW_COLOUR, LOW_COLOUR + colours - 1, f);
}

char* scanPerm(Perm p)  // Where the colours are given
{
    char s[MAX_POSITIONS + 1];
    fgets(s, MAX_POSITIONS + 1, stdin);
    if (isPerm(strreplace(s, '\n', '\0')))  // needs to discard the '\n' char
        return strcpy(p, s);
    else
        return NULL;
}

// 2nd PART of the master mind game (segundo subproblema)

Set sieve;
size_t maxperms;

char *Permlong(Perm p, size_t n)
{
    return stradd(stroflbw(p, colours, positions, n), LOW_COLOUR - '0');
}

size_t longPerm(Perm p)
{
    Perm p1;
    return lbofstr(stradd(strcpy(p1, p), '0' - LOW_COLOUR), colours);
}

void removePerms(Perm p, int b, int w)
{
    Perm p1;
    int w1;
    int b1;
    
    for (size_t i = 0; i < maxperms; i++)
    {
        if (Setisin(i, sieve))
        {
            Permcmp(p, Permlong(p1, i), &b1, &w1);
            if (b1 != b || w1 != w)
                Setrm(sieve, i);
        }
    }
}

Setelem Setrand(Set s)
{
    return Setpos(s, lNormRandomrng(1, Setcard(s)));
}

void choosePerm(Perm p)
{
    Permlong(p, Setpos(sieve, lNormRandom(Setcard(sieve) - 1) + 1));
}

int main()
{
    Perm secret;
    Perm play;
    
    int nplays;
    int black;  // perfect match
    int white;  // colour match only
    int eog;    // bool for "end of game"
    
    maxperms = ipow(colours, positions);
    printf("Playing with %d positions and %d colours.\n", positions, colours);
    printf("Number of permutations: %ld\n", maxperms);
    
    Setaddrng(Setclr(sieve), 0, maxperms - 1);
    nplays = 0;
    printf("Please choose a secret code and then type <return> to continue.");
    char dummy;
    scanf("%c", &dummy);  // consumes last '\n'
    //gets(line); // ???
    
    for (;;)
    {
        choosePerm(play);
        printf("My play #%d: %s\n", ++nplays, play);
        printf("blank: ");
        scanf("%d%*c", &black);    // "%*c" discards the '\n'
        
        if (black >= positions)
        {
            printf ("Right! Game over.\n");
            break;
        }
        
        printf("white: ");
        scanf("%d%*c", &white);     // "%*c" discards the '\n'
        
        removePerms(play, black, white);
        if (!Setcard(sieve))
        {
            printf("Error: no plays are possible.\n");
            break;
        }
    }
    
    return 0;
}
