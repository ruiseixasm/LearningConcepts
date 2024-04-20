// Compile command: gcc 01-master-mind-first.c random.c bags.c input.c -o 01-master-mind-first.out

#include <stdio.h>
#include <string.h>
#include "random.h"
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

int main()
{
    Perm secret;
    Perm play;
    
    int nplays;
    int black;  // perfect match
    int white;  // colour match only
    int eog;    // bool for "end of game"
    
    printf("Please enter number of positions (%d to %d): ", MIN_POSITIONS, MAX_POSITIONS);
    scanf("%d", &positions);
    printf("Please enter number of colours (%d to %d): ", MIN_COLOURS, MAX_COLOURS);
    scanf("%d", &colours);
    positions = setpositions(positions);
    colours = setcolours(colours);
    char dummy;
    scanf("%c", &dummy);  // consumes last '\n'
    //gets(line); // ???
    printf("Playing with %d positions and %d colours.\n", positions, colours);
    
    eog = 0;    // false
    nplays = 0;
    Permfunc(secret, crandrng);
    
    do
    {
        printf("Your play #%d: ", ++nplays);
        if (scanPerm(play))
        {
            eog = Permcmp(secret, play, &black, &white);
            printf("black %d, white %d.\n", black, white);
        }
        else
        {
            printf("Invalid play. Please re-enter.\n");
            --nplays;
        }
        
    } while (!eog);
    printf("Right!\n");
    
    return 0;
}
