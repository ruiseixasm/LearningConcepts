#ifndef LIB_DATA_BASE_IO
#define LIB_DATA_BASE_IO

#include <stdio.h>      // needed for FILE
#include "data_base.h"
#include "items.h"

// Save Data
void SaveDataBase(const FILE *f);
void DumpItems(const FILE *f, const Item *x, int n);
void WriteItem(const FILE *f, const Item *x);
void WriteDisk(const FILE *f, const Disk *d);
void DumpSongs(const FILE *f, const Song *s, int n);
void WriteSong(const FILE *f, const Song *s);

// Load Data


#endif /* LIB_DATA_BASE_IO */
