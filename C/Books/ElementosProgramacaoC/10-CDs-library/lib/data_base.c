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

// SELECTIONS

void SortSelected(int (*f)(const Item *, const Item *))
{
    SortPointers((void **)selected, n_selected,
                    (int(*)(const void *, const void *))f);
}

void RestrictSelected(int (*f)(const Item *))
{
    n_selected = RestrictPointers((void **)selected, n_selected,
                    (int(*)(const void *))f);
}

void SortByTitle(void)
{
    SortSelected(ItemLessThanByTitle);
}

void SortByArtist(void)
{
    SortSelected(ItemLessThanByArtist);
}

void SortByYear(void)
{
    SortSelected(ItemLessThanByYear);
}

static int ItemLessThanByTitle(const Item *t1, const Item *t2)
{
    return LessThanByTitle(&t1->disk, &t2->disk);
}

static int ItemLessThanByArtist(const Item *t1, const Item *t2)
{
    return LessThanByArtist(&t1->disk, &t2->disk);
}

static int ItemLessThanByYear(const Item *t1, const Item *t2)
{
    return LessThanByYear(&t1->disk, &t2->disk);
}

// RESTRICTIONS

void RestrictByArtistFull(Artist a)
{
    thisArtist = a;
    RestrictSelected(HasThisArtist);
}

void RestrictByTitleFull(Title t)
{
    thisTitle = t;
    RestrictSelected(HasThisTitle);
}

void RestrictByYear(Year y0, Year y1)
{
    thisYear0 = y0;
    thisYear1 = y1;
    RestrictSelected(IsInTheseYears);
}

void RestrictByStyle(Style s)
{
    thisStyle = s;
    RestrictSelected(HasThisStyle);
}

void RestrictBySongFull(const char *s)
{
    //thisSong = s;
    strcpy(thisSong, s);    // Has to make a copy because '*s' is a constant
    RestrictSelected(HasThisSong);
}

void RestrictByTitleApprox(Title t)
{
    thisTitle = strstndrd(t);
    RestrictSelected(HasThisTitleStndrd);
}

void RestrictByArtistApprox(Artist a)
{
    thisArtist = strstndrd(a);
    RestrictSelected(HasThisArtistStndrd);
}

void RestrictBySongApprox(const char *s)
{
    thisSong = strstndrd(strcpy(thisSong, s));
    if (strchr("aeiou", *thisSong) != NULL)
        strcpy(thisSong, thisSong + 1);
    RestrictSelected(HasThisSongStndrd);
}

static int HasThisArtist(const Item *t)
{
    return !strcmp(t->disk.artist, thisArtist);
}

static int HasThisTitle(const Item *t)
{
    return !strcmp(t->disk.title, thisTitle);
}

static int IsInTheseYears(const Item *t)
{
    return !(t->disk.year < thisYear0 || t->disk.year > thisYear1);
}

static int HasThisStyle(const Item *t)
{
    return t->disk.style == thisStyle;
}

static int HasThisSong(const Item *t)
{
    const Disk *d = &t->disk;
    for (size_t i = 0; i < d->n_songs; i++)
        if (strstr(d->songs[i].name, thisSong) != NULL)
            return 1;   // true
    return 0;           // false
}

static int HasThisArtistStndrd(const Item *t)
{
    char s[256];
    return !strcmp(strstndrd(strcpy(s, t->disk.artist)), thisArtist);
}

static int HasThisTitleStndrd(const Item *t)
{
    char s[256];
    return !strcmp(strstndrd(strcpy(s, t->disk.title)), thisTitle);
}

static int HasThisSongStndrd(const Item *t)
{
    char s[256];
    const Disk *d = &t->disk;
    const Song *g = d->songs;
    for (int n = d->n_songs; n; n--, g++)
        if (strstr(strstndrd(strcpy(s, g->name)), thisSong) != NULL);
            return 1;   // true
    return 0;           // false
}
