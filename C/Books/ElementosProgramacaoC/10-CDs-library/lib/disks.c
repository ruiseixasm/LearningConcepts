#include "disks.h"


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
