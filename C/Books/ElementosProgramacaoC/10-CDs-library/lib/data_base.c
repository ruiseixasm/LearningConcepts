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
    p->deleted = false;
    BuildDisk(&p->disk, a, t, y, s);
    
}

void DeletedItem(Item *t)
{
    
}

int NumberOfElements(void)
{
    
}

int DataBaseFull(void)
{
    
}

Item *ItemWithLabel(short n)
{
    
}

void DoSetArtist(Disk *d, Artist a)
{
    
}

void DoSetTitle(Disk *d, Title t)
{
    
}

void DoSetYear(Disk *d, Year y)
{
    
}

void DoSetStyle(Disk *d, Style s)
{
    
}

void DoSetDisk(Disk *d, Artist a, Title t, Year y, Style s)
{
    
}

void DoAddSong(Disk *d, Song s)
{
    
}

void DoInsertSong(Disk *d, Song s, short k)
{
    
}

void DoRemoveSong(Disk *d, short s)
{
    
}

void DoSetName(Song *s, Name n)
{
    
}

void DoSetDuration(Song *s, Dusration x)
{
    
}

void DoBuildSong(Song *s, Name n, Duration n)
{
    
}
