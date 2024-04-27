#include "disks.h"

int IsYear(int n)
{
    return 1877 <= n && n <= MAX_YEAR;
}

const char *StyleNameOf(Style s)
{
    return style_names[s - 1];
}

Disk MakeDisk(Artist a, Title t, Year y, Style s)
{
    Disk d;
    d.artist    = a;
    d.title     = t;
    d.year      = y;
    d.style     = s;
    d.n_songs   = 0;
    return d;
}

void BuildDisk(Disk *d, Artist a, Title t, Year y, Style s)
{
    d->artist   = a;
    d->title    = t;
    d->year     = y;
    d->style    = s;
    d->n_songs  = 0;
}

void AddSong(Disk *d, Song s)
{
    d->songs[(d->n_songs)++] = s;
}

void SetArtist(Disk *d, Artist a)
{
    d->artist   = a;
}

void SetTitle(Disk *d, Title t)
{
    d->title    = t;
}

void SetYear(Disk *d, Year y)
{
    d->year     = y;
}

void SetStyle(Disk *d, Style s)
{
    d->style    = s;
}

void SetDisk(Disk *d, Artist a, Title t, Year y, Style s)
{
    d->artist   = a;
    d->title    = t;
    d->year     = y;
    d->style    = s;
}

void RemoveSong(Disk *d, short n)
{
    // Songs are enumerated from 1 and not from 0 (n > 0)!
    for (size_t i = n; i < d->n_songs; i++)
        d->songs[i - 1] = d->songs[i];
    d->n_songs--;
}

void InsertSong(Disk *d, Song s, short n)
{
    // Songs are enumerated from 1 and not from 0 (n > 0)!
    for (size_t i = d->n_songs; i >= n; i--)
        d->songs[i] = d->songs[i - 1];
    d->songs[n - 1] = s;
    d->n_songs++;
}


int LessThanByArtist(const Disk *d1, const Disk *d2)
{
    int cmp;
    return
        (cmp = strcmp(d1->artist, d2->artist)) < 0 ||
         cmp == 0 && (d1->year < d2->year || d1-> year == d2->year &&
            strcmp(d1->title, d2->title) <= 0);
}

int LessThanByTitle(const Disk *d1, const Disk *d2)
{
    int cmp;
    return
        (cmp = strcmp(d1->title, d2->title)) < 0 ||
         cmp == 0 && (d1->year < d2->year || d1->year == d2->year &&
            strcmp(d1->artist, d2->artist) <= 0);         
}

int LessThanByYear(const Disk *d1, const Disk *d2)
{
    int cmp;
    return
        d1->year < d2->year || d1->year == d2->year &&
           ((cmp = strcmp(d1->artist, d2->artist)) < 0 ||
             cmp == 0 && strcmp(d1->title, d2->title) <= 0);
}
