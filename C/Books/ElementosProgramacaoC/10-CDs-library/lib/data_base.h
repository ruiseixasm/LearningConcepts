#ifndef LIB_DATA_BASE
#define LIB_DATA_BASE

#include "ppvoid.h"
#include "items.h"
#include "string_util.h"

#define MAX_ITEMS   1024

// static means file scoped, invisible from other files (translation units)
static Item items[MAX_ITEMS];
static int n_items;
static int n_deleted;
static int n_modifs;
static int next_label;

void ClearDataBase(void);
Item *AddItem(Artist a, Title t, Year y, Style s);
void DeletedItem(Item *t);
int NumberOfElements(void);
int NumberOfModifs(void);
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
void DoSetDuration(Song *s, Duration x);
void DoBuildSong(Song *s, Name n, Duration x);

// SELECTIONS

static Item *selected[MAX_ITEMS];   // Item pointers array
static int n_selected;

void SortSelected(int (*f)(const Item *, const Item *));
void RestrictSelected(int (*f)(const Item *));

void SortByTitle(void);
void SortByArtist(void);
void SortByYear(void);

static int ItemLessThanByTitle(const Item *t1, const Item *t2);
static int ItemLessThanByArtist(const Item *t1, const Item *t2);
static int ItemLessThanByYear(const Item *t1, const Item *t2);

// RESTRICTIONS

void RestrictByArtistFull(Artist a);
void RestrictByTitleFull(Title t);
void RestrictByYear(Year y0, Year y1);
void RestrictByStyle(Style s);
void RestrictBySongFull(const char *s);

void RestrictByTitleApprox(Title t);
void RestrictByArtistApprox(Artist a);
void RestrictBySongApprox(const char *s);

static Artist thisArtist;
static int HasThisArtist(const Item *t);
static Title thisTitle;
static int HasThisTitle(const Item *t);
static Year thisYear0;
static Year thisYear1;
static int IsInTheseYears(const Item *t);
static Style thisStyle;
static int HasThisStyle(const Item *t);
static char *thisSong;
static int HasThisSong(const Item *t);



#endif /* LIB_DATA_BASE */
