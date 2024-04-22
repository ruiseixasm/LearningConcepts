#include "data_base.h"


void ClearDataBase(void)
{
    n_items     = 0;
    n_deleted   = 0;
    next_label  = 1;
    n_modifs    = 0;
}

Item *AddItem(Artist a, Title t, Year y, Style s)
{
    Item *p = items + n_items++;
    p->label = next_label++;
    p->deleted = 0; // false
    BuildDisk(&p->disk, a, t, y, s);
    n_modifs;
    return p;
}

void DeletedItem(Item *t)
{
    MarkDeleted(t);
    n_modifs++;
    n_deleted++;
}

int NumberOfElements(void)
{
    return n_items - n_deleted;
}

int NumberOfModifs(void)
{
    return n_modifs;
}

int DataBaseFull(void)
{
    return n_items == MAX_ITEMS;
}

Item *ItemWithLabel(short n)
{
    short a;
    short i = 0;
    short j = n_items - 1;
    while (i < j)
        if (n <= items[a = (i + j)/2].label)
            j = a;
        else
            i = a + 1;
    return i == j && !items[i].deleted &&
           n == items[i].label ? items + i : NULL;
}

void DoSetArtist(Disk *d, Artist a)
{
    SetArtist(d, a);
    n_modifs++;
}

void DoSetTitle(Disk *d, Title t)
{
    SetTitle(d, t);
    n_modifs++;
}

void DoSetYear(Disk *d, Year y)
{
    SetYear(d, y);
    n_modifs++;
}

void DoSetStyle(Disk *d, Style s)
{
    SetStyle(d, s);
    n_modifs++;
}

void DoSetDisk(Disk *d, Artist a, Title t, Year y, Style s)
{
    SetDisk(d, a, t, y, s);
    n_modifs++;
}

void DoAddSong(Disk *d, Song s)
{
    AddSong(d, s);
    n_modifs++;
}

void DoInsertSong(Disk *d, Song s, short k)
{
    InsertSong(d, s, k);
    n_modifs++;
}

void DoRemoveSong(Disk *d, short s)
{
    RemoveSong(d, s);
    n_modifs++;
}

void DoSetName(Song *s, Name n)
{
    SetName(s, n);
    n_modifs++;
}

void DoSetDuration(Song *s, Duration x)
{
    SetDuration(s, x);
    n_modifs++;
}

void DoBuildSong(Song *s, Name n, Duration x)
{
    BuildSong(s, n, x);
    n_modifs++;
}
