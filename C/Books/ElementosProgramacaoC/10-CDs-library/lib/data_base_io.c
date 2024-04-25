#include "data_base_io.h"

// Save Data

void SaveDataBase(FILE *f)
{
    fprintf(f, "%d\n", next_label);
    fprintf(f, "%d\n", n_items);
    DumpItems(f, items, n_items);
    n_modifs = 0;
}

void DumpItems(FILE *f, const Item *x, int n)
{
    while (n--)
        WriteItem(f, x++);
}

void WriteItem(FILE *f, const Item *x)
{
    fprintf(f, "%d\n%d\n", x->label, x->deleted);
    WriteDisk(f, &(x->disk));
}

void WriteDisk(FILE *f, const Disk *d)
{
    fprintf(f, "%s\n%s\n%d\n%d\n%d\n",
                d->artist, d->title, d->year, d->style, d->n_songs);
    DumpSongs(f, d->songs, d->n_songs);
}

void DumpSongs(FILE *f, const Song *s, int n)
{
    while (n--)
        WriteSong(f, s++);
}

void WriteSong(FILE *f, const Song *s)
{
    fprintf(f, "%s\n%d\n", s->name, s->duration);
}

// Load Data

void readstr(FILE *f, char **s)
{
    char line[256]; // buffer for entire line of text
    fgets(line, sizeof(line), f);
    line[strlen(line) - 1] = '\0';  // replaces '\n' with '\0'
    *s = strnew(line);  // adds line to the array of lines (**)
}

void fscanint(FILE *f, int *x)
{
    fscanf(f, "%d%*c", x);  // "%*c" - skips '\n' char
}

void OpenDataBase(FILE *f)
{
    fscanint(f, (int*)&next_label);
    fscanint(f, (int*)&n_items);
    LoadItems(f, items, n_items);
    ResetSelection();
    n_modifs = 0;
    n_deleted = n_items - n_selected;
}

void LoadItems(FILE *f, Item *x, int n)
{
    while (n--)
        ReadItem(f, x++);
}

void ReadItem(FILE *f, Item *x)
{
    fscanint(f, (int*)&(x->label));
    fscanint(f, (int*)&(x->deleted));
    ReadDisk(f, &(x->disk));
}

void ReadDisk(FILE *f, Disk *d)
{
    Artist a;
    Title t;
    Year y;
    Style s;
    int n_songs;
    int x;
    Name n;
    
    readstr(f, &a);
    readstr(f, &t);
    fscanint(f, (int*)&y);
    fscanint(f, (int*)&s);
    BuildDisk(d, a, t, y, s);
    fscanint(f, &n_songs);
    LoadSongs(f, d->songs, n_songs);
    d->n_songs = n_songs;
}

void LoadSongs(FILE *f, Song *s, int n)
{
    while (n--)
        ReadSong(f, s++);
}

void ReadSong(FILE *f, Song *s)
{
    Name n;
    Duration d;
    readstr(f, &n); // passes as **s (*Name), array of strings
    fscanint(f, (int*)&d);
    BuildSong(s, n, d);
}

// Display Data

static void DisplayItemOnThisFile(Item *t)
{
    DisplayItem(thisFile, t);
}

void DisplaySelection(FILE *f)
{
    thisFile = f;
    IterateSelection(DisplayItemOnThisFile);
}

void DisplayItem(FILE *f, const Item *t)
{
    fprintf(f, "Etiqueta: %d\n", t->label);
    DisplayDisk(f, &t->disk);
}

void DisplayDiskMainInfo(FILE *f, const Disk *d)
{
    char style[64];
    fprintf(f, "Artista: %s\nTítulo:  %s\n"
               "Ano de edição: %d\nEstilo: %s\n",
               d->artist, d->title, d->year,
               StyleNameOf(style, d->style));
}

void DisplaySongInDisk(FILE *f, const Disk *d)
{
    DisplaySongs(f, d->songs, d->n_songs);
}

void DisplayDisk(FILE *f, const Disk *d)
{
    DisplayDiskMainInfo(f, d);
    DisplaySongInDisk(f, d);
}

void DisplaySong(FILE *f, const Song *s, int i)
{
    fprintf(f, "%2d - %s (%d s.)\n", i, s->name, s->duration);
}

void DisplaySongs(FILE *f, const Song *s, int n)
{
    int i = 1;
    fprintf(f, "Canções:\n");
    while (n--)
        DisplaySong(f, s++, i++);
}
