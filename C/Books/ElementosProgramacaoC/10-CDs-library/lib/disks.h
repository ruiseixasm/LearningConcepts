#ifndef LIB_DISKS
#define LIB_DISKS

#include <stddef.h>
#include <string.h>
#include "songs.h"

typedef char *Artist;
typedef char *Title;
typedef short Year;
typedef short Style;

#define NUMBER_OF_STYLES    6
#define MAX_SONGS           24

typedef struct {
    Artist  artist;
    Title   title;
    Year    year;
    Style   style;
    short   n_songs;
    Song    songs[MAX_SONGS];
} Disk;

Disk MakeDisk(Artist a, Title t, Year y, Style s);
void BuildDisk(Disk *d, Artist a, Title t, Year y, Style s);
void AddSong(Disk *d, Song s);
void SetArtist(Disk *d, Artist a);
void SetTitle(Disk *d, Title t);
void SetYear(Disk *d, Year y);
void SetStyle(Disk *d, Style s);
void SetDisk(Disk *d, Artist a, Title t, Year y, Style s);
void RemoveSong(Disk *d, short n);
void InsertSong(Disk *d, Song s, short n);

int LessThanByArtist(const Disk *d1, const Disk *d2);
int LessThanByTitle(const Disk *d1, const Disk *d2);
int LessThanByYear(const Disk *d1, const Disk *d2);


#endif /* LIB_DISKS */
