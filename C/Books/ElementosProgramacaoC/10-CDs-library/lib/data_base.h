#ifndef LIB_DATA_BASE
#define LIB_DATA_BASE

#include "ppvoid.h"
#include "items.h"

#define MAX_ITEMS   1024

// static means file scoped, inveisible on other files (translation units)
static Item items[MAX_ITEMS];
static int n_items;
static int n_deleted;
static int n_modifs;
static int next_label;

void ClearDataBase(void);
Item *AddItem(Artist a, Title t, Year y, Style s);
void DeletedItem(Item *t);
int NumberOfElements(void);
int DataBaseFull(void);
Item *ItemWithLabel(short n);
void DoSetArtist(Disk *d, Artist a);
void DoSetTitle(Disk *d, Title t);
void DoSetYear(Disk *d, Year y);
void DoSetStyle(Disk *d, Style s);
void DoSetDisk(Disk *d, Artist a, Title t, Year y, Style s);
void DoAddSong(Disk *d, Song s);
void DoInsertSong(Disk *d, Song s, short k);
void DoRemoveSong(Disk *d, short s);
void DoSetName(Song *s, Name n);
void DoSetDuration(Song *s, Dusration x);
void DoBuildSong(Song *s, Name n, Duration n);

#endif /* LIB_DATA_BASE */
