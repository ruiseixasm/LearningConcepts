// Compile command: gcc 03-master-mind-third.c sets.c bags.c utils.c -DSET_MAX=59048 -o 03-master-mind-third.out

#include <stdio.h>
#include <string.h>
#include <stddef.h>     // for size_t
#include "sets.h"
#include "bags.h"
#include "utils.h"

#define POSITIONS       5               // Used         +
#define COLOURS         9               // Used         +
#define LOW_COLOUR      '1'             // Used         +
#define HIGH_COLOUR     '0' + COLOURS   // Not used!    -

int positions   = POSITIONS;
int colours     = COLOURS;

                             // + 1 to allow '\0' at the end (avoids memory leak!)
typedef char Perm[POSITIONS + 1];   // global variable that by default all elements are 0

// 1st PART of the master mind game (primeiro subproblema)

int btwn(int x, int a, int b)
{
    return x < a ? a : x > b ? b : x;    
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
    *s = '\0';      // same as 0, the reason why Perm[POSITIONS + 1] (+ 1)
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
    char s[POSITIONS + 1];
    fgets(s, POSITIONS + 1, stdin);
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

// 3th PART of the master mind game (outra estratégia)

typedef struct
{
    Perm play;
    int black;
    int white;
} Score;

#define MAX_GAME 12
Score game[MAX_GAME];
int nplays;

int ispossible(Perm p)
{
    int b;
    int w;
    int i;
    Score *s;
    for (i = 0, s = game; i < nplays; i++, s++)
    {
        Permcmp(p, s->play, &b, &w);
        if (b != s->black || w != s->white)
            return 0;
    }
    return 1;
}

int choosePerm(Perm p, size_t *next, size_t first)
{
    for (;;)
    {
        if (ispossible(Permlong(p, *next)))
            return 1;
        *next = ++*next % maxperms;
        if (*next == first)
            return 0;   // No possible solution has been found!!
    }
}

int main()
{
    Perm play;
    
    int black;  // perfect match
    int white;  // colour match only
    
    size_t first;
    size_t next;

    maxperms = ipow(colours, positions);
    printf("Playing with %d positions and %d colours.\n", positions, colours);
    printf("Number of permutations: %ld\n", maxperms);
    
    first = lNormRandom(maxperms);
    next = first;
    nplays = 0;

    printf("Please choose a secret code and then type <return> to continue."); // Computer never know the real secret
    getchar();  // awaits for key <return>
    
    for (;;)
    {
        if (!choosePerm(play, &next, first))
        {
            printf("Error: no plays are possible.\n\n");
            break;
        }

        printf("My play #%d: %s\n", nplays + 1, play);

        printf("Black: ");
        scanf("%d%*c", &black);
        if (black >= positions)
        {
            printf ("Right! Game over.\n\n");
            break;
        }
        
        printf("White: ");
        scanf("%d%*c", &white);

        strcpy(game[nplays].play, play);
        game[nplays].black = black;
        game[nplays].white = white;

        if (++nplays == MAX_GAME)
        {
            printf("Wrong! Too many plays in this game. Game over.\n\n");
            break;
        }
    }

    press_any_key();
    
    return 0;
}
