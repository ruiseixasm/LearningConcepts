// Compile command: gcc music.c lib/utils.c lib/data_base.c lib/data_base_io.c lib/dialogs.c -o music.out
#include "lib/utils.h"          // My own library
#include "lib/data_base.h"
#include "lib/data_base_io.h"
#include "lib/dialogs.h"
#include "lib/int_util.h"

#define UNABLE_TO_WRITE "Unable to write file. "
#define UNABLE_TO_READ  "Unable to read file. "

Menu mainMenu;      // A
Menu fileMenu;      // B
Menu diskMenu;      // C
Menu styleMenu;     // D
Menu searchMenu;    // E
Menu sortMenu;      // F
Menu selectMenu;    // G

int dbOpen;     // boolean
char dbName[64];
int searchApprox = 0;
char style_name[64];    // needed for safe StyleNameOf(char *style_name, const Style s)

typedef void (*fRestrict)(const char *);
fRestrict RestrictByArtist[2]   = {RestrictByArtistFull, RestrictByArtistApprox};
fRestrict RestrictByTitle[2]    = {RestrictByTitleFull, RestrictByTitleApprox};
fRestrict RestrictBySong[2]     = {RestrictBySongFull, RestrictBySongApprox};

// AUXILIAR
int istrlen(const char *s);

// MENUS
int DoMainMenu(void);
void DoFileMenu(void);
void DoDisksMenu(void);
void DoSearchMenu(void);
void DoSortMenu(void);
void DoSelectMenu(void);
void DoDisplaySelection(void);

// ITEMS
void DoAddItems(void);
void DoDisplayItems(void);
void DoEditItems(void);
void DoDeleteItems(void);

// DISKS
void DoEditDisk(Disk *d);
int DoEditMainInfo(Disk *d);
void DoEditSongs(Disk *d);

// SONGS
void DoEditOneSong(Disk *d);
void DoDeleteOneSong(Disk *d);
void DoInsertOneSong(Disk *d);
void DoAddOneSong(Disk *d);

int main(int argc, char *argv[])
{
    printf("Total arguments: %d\n", argc);
    printf("Arguments:");
    for (int i = 0; i < argc; i++)
        printf(" %s", argv[i]);
    printf("\n");


    /* inicialização dos menus */
    // Main Menu    (A)
    CreateMenu(&mainMenu, "MAIN MENU", "file>>;disks>>;search>>;quit;");
    // File Menu    (B)
    CreateMenu(&fileMenu, "FILE", "new;open...;close;save;save as...;abandon;");
    // Disk Menu    (C)
    CreateMenu(&diskMenu, "DISKS", "new...;inspect...;edit...;delete...;");
    // Styles Menu  (D)
    CreateMenu(&styleMenu, "Style: ", "");
    for (int i = 1; i <= NUMBER_OF_STYLES; i++)
        AppendItem(&styleMenu, StyleNameOf(i));
    // Search Menu  (E)
    CreateMenu(&searchMenu, "SEARCH", "restart;use aproximations;select>>;"
                                      "sort>>;display;print...;;"); // Last element is the 7th
    DisableItem(&searchMenu, 7);    // Disables last element (7th)
    // Sort Menu    (F)
    CreateMenu(&sortMenu, "sort by", "artist;title;year;");
    // Select Menu  (G)
    CreateMenu(&selectMenu, "select by", "artist...;title...;year...;style...;song...;");

    ClearDataBase();
    dbOpen = 0; // false
    while (DoMainMenu()) {}
    
    return 0;
}


// AUXILIAR

int istrlen(const char *s)
{
    return strlen(s);
}

// MENUS

int DoMainMenu(void)
{
    return 0;
}

void DoFileMenu(void)
{
    
}

void DoDisksMenu(void)
{
    
}

void DoSearchMenu(void)
{
    
}

void DoSortMenu(void)
{
    
}

void DoSelectMenu(void)
{
    
}

void DoDisplaySelection(void)
{
    
}

// ITEMS

void DoAddItems(void)
{
    
}

void DoDisplayItems(void)
{
    
}

void DoEditItems(void)
{
    
}

void DoDeleteItems(void)
{
    
}

// DISKS

void DoEditDisk(Disk *d)
{
    
}

int DoEditMainInfo(Disk *d)
{
    return 0;
}

void DoEditSongs(Disk *d)
{
    
}

// SONGS

void DoEditOneSong(Disk *d)
{
    
}

void DoDeleteOneSong(Disk *d)
{
    
}

void DoInsertOneSong(Disk *d)
{
    
}

void DoAddOneSong(Disk *d)
{

}
