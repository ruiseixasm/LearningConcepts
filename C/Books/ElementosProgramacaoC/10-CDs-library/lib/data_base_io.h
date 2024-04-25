#ifndef LIB_DATA_BASE_IO
#define LIB_DATA_BASE_IO

#include <stdio.h>      // needed for FILE
#include "data_base.h"
#include "items.h"

// Save Data
void SaveDataBase(FILE *f);
void DumpItems(FILE *f, const Item *x, int n);
void WriteItem(FILE *f, const Item *x);
void WriteDisk(FILE *f, const Disk *d);
void DumpSongs(FILE *f, const Song *s, int n);
void WriteSong(FILE *f, const Song *s);

// Load Data
void readstr(FILE *f, char **s);
void fscanint(FILE *f, int *x);
void OpenDataBase(FILE *f);
void LoadItems(FILE *f, Item *x, int n);
void ReadItem(FILE *f, Item *x);
void ReadDisk(FILE *f, Disk *d);
void LoadSongs(FILE *f, Song *s, int n);
void ReadSong(FILE *f, Song *s);

// Display Data
static FILE     *thisFile;

static void DisplayItemOnThisFile(Item *t); // To be passed to IterateSelection
void DisplaySelection(FILE *f);
void DisplayItem(FILE *f, const Item *t);
void DisplayDiskMainInfo(FILE *f, const Disk *d);
void DisplaySongInDisk(FILE *f, const Disk *d);
void DisplayDisk(FILE *f, const Disk *d);
void DisplaySong(FILE *f, const Song *s, int i);
void DisplaySongs(FILE *f, const Song *s, int n);

#endif /* LIB_DATA_BASE_IO */
