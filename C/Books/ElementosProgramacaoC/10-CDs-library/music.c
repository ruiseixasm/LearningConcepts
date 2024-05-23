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
int DoSortMenu(void);
int DoSelectMenu(void);
void DoDisplaySelection(void);

// ITEMS
void DoAddItems(void);
int SelectItem(Item **x);
void DoDisplayItems(void);
void DoEditItems(void);
void DoDeleteItems(void);
int NumberOfSelectedItems();    // Missing function, consideres check as same as selected!

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
    EnableItemCond(&mainMenu, 2, dbOpen);
    EnableItemCond(&mainMenu, 3, dbOpen && NumberOfElements());

    switch (MenuSelect(&mainMenu))
    {
        case 0: return 1;
        case 1:
            DoFileMenu();
            return 1;
        case 2:
            DoDisksMenu();
            return 1;
        case 3:
            DoSearchMenu();
            return 1;
        case 4:
            if (NumberOfModifs())
                switch (ButtonSelect("Quit without saving? ", "No;Yes;Save;"))
                {
                    case 1: return 1;
                    case 2: return 0;
                    case 3:
                    {
                        FILE *db;
                        if ((db = fopen(dbName , "w")) != NULL ||
                            (OpenFileBox(dbName, &db, "Save in which file? ", "w", UNABLE_TO_WRITE)))
                        {
                            SaveDataBase(db);
                            fclose(db);
                            return 0;
                        }
                    }
                    
                    default: return 1;
                }
    
        default: return 0;
    }
}

void DoFileMenu(void)
{
    int i_sel;
    FILE *db;
    EnableItemCond(&fileMenu, 1, !dbOpen);
    EnableItemCond(&fileMenu, 2, !dbOpen);
    EnableItemCond(&fileMenu, 3, dbOpen && *dbName != '\0');
    EnableItemCond(&fileMenu, 4, dbOpen && *dbName != '\0' && NumberOfModifs());
    EnableItemCond(&fileMenu, 5, dbOpen);
    EnableItemCond(&fileMenu, 6, dbOpen);

    switch (i_sel = MenuSelect(&fileMenu))
    {
        case 0: return;
        case 1:
            ClearDataBase();
            dbOpen = 1; // true
            *dbName = '\0';
            return;
        case 2:
            if (OpenFileBox(dbName, &db, "Open which file? ", "r", UNABLE_TO_READ))
            {
                OpenDataBase(db);
                fclose(db);
                dbOpen = 1; // true
            }
            return;
        case 3:
        case 4:
            if (NumberOfModifs())
                if ((db = fopen(dbName, "w")) == NULL)
                {
                    ErrorBox("Unable to close file. ");
                }
                else
                {
                    SaveDataBase(db);
                    fclose(db);
                }
            if (i_sel == 3)
                dbOpen = 0;
            return;
        case 5:
            if (OpenFileBox(dbName, &db, "save in which file? ", "w", UNABLE_TO_WRITE))
            {
                SaveDataBase(db);
                fclose(db);
            }
            return;
        case 6:
            if (!NumberOfModifs() || NoYesBox("Discard edits in this data base? "))
                dbOpen = 0; // false
            return;

        default:
            break;
    }
}

void DoDisksMenu(void)
{
    int n_elems = NumberOfElements();
    EnableItemCond(&diskMenu, 2, n_elems);
    EnableItemCond(&diskMenu, 3, n_elems);
    EnableItemCond(&diskMenu, 4, n_elems);

    switch (MenuSelect(&diskMenu))
    {
        case 0: return;
        case 1:
            if (DataBaseFull())
                ErrorBox("Data base is full.\nUnable to add disks. ");
            else
                DoAddItems();
            return;
        case 2:
            DoDisplayItems();
            return;
        case 3:
            DoEditItems();
            return;
        case 4:
            DoDeleteItems();
            return;

        default:
            break;
    }
}

void DoSearchMenu(void)
{
    FILE *listFile;
    char listFileName[256];
    char name[64];
    int n_sel;
    
    sprintf(name, "(#selected = %d)", n_sel = NumberOfSelectedItems());
    RenameItem(&searchMenu, 7, name);
    CheckItemCond(&searchMenu, 2, searchApprox);
    EnableItemCond(&searchMenu, 3, n_sel);
    EnableItemCond(&searchMenu, 4, n_sel);
    EnableItemCond(&searchMenu, 5, n_sel);
    EnableItemCond(&searchMenu, 6, n_sel);
    
    switch(MenuSelect(&searchMenu))
    {
        case 0: return;
        case 1:
            ResetSelection();
            return;
        case 2:
            searchApprox = !searchApprox;
            return;
        case 3:
            if (DoSelectMenu())
                DoDisplaySelection();
            return;
        case 4:
            if (DoSortMenu())
                DoDisplaySelection();
            return;
        case 5:
            DisplaySelection(stdout);
            return;
        case 6:
            if (OpenFileBox(listFileName, &listFile,
                            "Print in which file? ", "w",
                            UNABLE_TO_WRITE))
            {
                DisplaySelection(listFile);
                fclose(listFile);
            }
            return;
            
        default: break;
    }
}

int DoSortMenu(void)
{
    switch(MenuSelect(&sortMenu))
    {
        case 0: return 0;
        case 1:
            SortByArtist();
            return 1;
        case 2:
            SortByTitle();
            return 1;
        case 3:
            SortByYear();
            return 1;
            
        default: return 0;
    }
}

int DoSelectMenu(void)
{
    switch(MenuSelect(&selectMenu))
    {
        case 0: return 0;
        case 1:
        {
            Artist a;
            if (ReadString(&a, "Artist: ", NULL, ""))
            {
                RestrictByArtist[searchApprox](a);
                return 1;
            }
            else
                return 0;
        }
        case 2:
        {
            Title t;
            if (ReadString(&t, "Title: ", NULL, ""))
            {
                RestrictByTitle[searchApprox](t);
                return 1;
            }
            else
                return 0;
        }
        case 3:
        {
            int y0_int, y1_int;
            if (ReadInt(&y0_int, "First year: ", NULL, "") &&
                ReadInt(&y1_int, "Last year:  ", NULL, ""))
            {
                RestrictByYear((Year)y0_int, (Year)y1_int);
                return 1;
            }
            else
                return 0;
        }
        case 4:
        {
            Style s;
            if (s = MenuSelect(&styleMenu))
            {
                RestrictByStyle(s);
                return 1;
            }
            else
                return 0;
        }
        case 5:
        {
            char *s;
            if (ReadString(&s, "Name of song (or part of it): ", NULL, ""))
            {
                RestrictBySong[searchApprox](s);
                return 1;
            }
            else
                return 0;
        }
        
        default: break;
    }
}

void DoDisplaySelection(void)
{
    char message[64];
    char buttons[32];
    
    for (;;)
    {
        sprintf(message, "Number of selected items = %d\n", NumberOfSelectedItems());
        strcpy(buttons, NumberOfSelectedItems() ?
                        "OK;Display;Restart;" :"OK;;Restart;");
                        
        switch (ButtonSelect(message, buttons))
        {
            case 1: return;
            case 2:
                DisplaySelection(stdout);
                break;
            case 3:
                ResetSelection();
                strcpy(buttons, "OK;Display;");
                break;
        }
    }
}

// ITEMS

void DoAddItems(void)
{
    Artist a;
    Title t;
    Year y;
    Style s;
    Item *x;
    char message[32];

    while (DialogBox("Add a new disk (type '$' to CANCEL)\n%s%s%d%m",
            &a, "Artist: ", istrlen, "This field must be non-empty. ",
            &t, "Title:  ", NULL, "",
            &y, "Year: ", IsYear, "Invalid year. ",
            &s, &styleMenu))
    {
        printf("Lable = %d\n", (x = AddItem(a, t, y, s))->label);
        DoEditDisk(&x->disk);
    }
}

int SelectItem(Item **x)
{
    int n;
    while (ReadInt(&n, "Label number: ", NULL, ""))
        if ((*x = ItemWithLabel(n)) == NULL)
            ErrorBox("No such label. ");
        else
        {
            DisplayItem(stdout, *x);
            return 1;
        }
    return 0;
}

void DoDisplayItems(void)
{
    Item *x;
    //                               Only the last operand is considered for the while evaluation
    while (printf("Inspect disk\n"), SelectItem(&x)) {}
}

void DoEditItems(void)
{
    Item *x;
    while (printf("Edit disk\n"), SelectItem(&x))
        DoEditDisk(&x->disk);
}

void DoDeleteItems(void)
{
    Item *x;
    while (printf("Delete disk\n"), SelectItem(&x))
        switch (ButtonSelect("Delete this disk? ", "No;Yes;Cancel;"))
        {
            case 1: break;
            case 2:
                DeleteItem(x);
                if (!NumberOfElements())
                    return;
                break;
            case 3: return;
            
            default: break;
        }
}

int NumberOfSelectedItems()     // Missing function, consideres check as same as selected!
{
    int total_selected = 0;
    MenuItem *menu_items = searchMenu.items;
    for (int i = 0; i < searchMenu.n_Items; i++)
        total_selected += menu_items[i].checked;
    
    return total_selected;
}

// DISKS

void DoEditDisk(Disk *d)
{
    switch (ButtonSelect("Edit this disk? ", "No;Yes;Songs;"))
    {
        case 1: break;
        case 2:
            if (DoEditMainInfo(d))
                DoEditSongs(d);
            return;
        case 3:
            DoEditSongs(d);
            return;
    }
}

int DoEditMainInfo(Disk *d)
{
    Artist  a = d->artist;
    Title   t = d->title;
    Year    y = d->year;
    Style   s = d->style;
    
    if (DialogBox("Edit a disk\n%S%S%D%M",
                  &a, "Artist [%s]: ", istrlen, "This field must be non-empty. ",
                  &t, "Title [%s]: ", NULL, "",
                  &y, "Year [%d]: ", IsYear, "Invalid year. ",
                  &s, &styleMenu))
    {
        DoSetDisk(d, a, t, y, s);
        return 1;   // true
    }
    else
        return 0;   // false
}

void DoEditSongs(Disk *d)
{
    int s_number;
    for (;;)
        switch (ButtonSelect ("Songs? ", d->n_songs ?
                "OK;See;Edit;Delete;Insert;Add;" :
                "OK;;;;Insert;Add;"))
        {
            case 1: return;
            case 2:
                DisplaySongsInDisk(stdout, d);
                break;
            case 3:
                DoEditOneSong(d);
                break;
            case 4:
                DoDeleteOneSong(d);
                break;
            case 5:
                DoInsertOneSong(d);
                break;
            case 6:
                DoAddOneSong(d);
                break;
                
            default: break;
        }
}

// SONGS

void DoEditOneSong(Disk *d)
{
    int s_number;
    Song *s_ref;
    Name name;
    int duration;
    
    if (ReadInt(&s_number, "song number ",
                ispos, "Invalid song number. "))
    {
        s_number = min(s_number, d->n_songs);
        s_ref = d->songs + s_number - 1;
        name = s_ref->name;
        duration = s_ref->duration;
        DisplaySong(stdout, s_ref, s_number);
        if (DialogBox("Edit a song\n%S%D",
                      &name, "Name[%s]: ", NULL, "",
                      &duration, "Duration[%d]: ", IsDuration, "Invalid value. "))
            DoBuildSong(s_ref, name, duration);
        DisplaySong(stdout, s_ref, s_number);
    }
}

void DoDeleteOneSong(Disk *d)
{
    int s_number;
    Song *s_ref;
    if (ReadInt(&s_number, "song number ", ispos, "Invalid song number. "))
    {
        s_number = min(s_number, d->n_songs);
        s_ref = d->songs + s_number - 1;
        DisplaySong(stdout, s_ref, s_number);
        if (NoYesBox("Delete this song? "))
            DoRemoveSong(d, s_number);
    }
}

void DoInsertOneSong(Disk *d)
{
    int s_number;
    Name name;
    int duration;
    if (d->n_songs == MAX_SONGS)
    {
        ErrorBox("Disk is full. Cannot insert. ");
        return;
    }
    if (ReadInt(&s_number, "song number ", ispos, "Invalid song number. "))
        if (DialogBox("Insert a song\n%s%d",
                      &name, "Name: ", NULL, "",
                      &duration, "Duration: ", IsDuration, "Invalid value. "))
            DoInsertSong(d, MakeSong(name, duration), min(s_number, d->n_songs + 1));
}

void DoAddOneSong(Disk *d)
{
    Name name;
    int duration;
    if (d->n_songs == MAX_SONGS)
    {
        ErrorBox("Disk is full. Cannot add. ");
        return;
    }
    if (DialogBox("Add a song\n%s%d",
                  &name, "Name: ", NULL, "",
                  &duration, "Duration: ", IsDuration, "Invalid value. "))
        DoAddSong(d, MakeSong(name, duration));
}
