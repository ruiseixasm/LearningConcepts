#ifndef LIB_MENUS
#define LIB_MENUS

#include <stdio.h>
#include <ctype.h>  // nedded for isdigit()
#include <stdlib.h> // needed for atoi(), malloc(), calloc() and free()
#include "string_util.h"    // needed for strnew()
#include "utils.h"  // needed for gets_string()

#define MAX_MENU_ITEMS  16

typedef struct {
    char *name;
    int enabled;
    int checked;
} MenuItem;

typedef struct {
    char *title;
    MenuItem items[MAX_MENU_ITEMS];
    int n_Items;
} Menu;

static void DisplayMenu(const Menu *m);
int MenuSelect(const Menu *m);

void CreateMenu(Menu *m, const char *t, const char *s);
void AppendItem(Menu *m, const char *s);
void EnableItem(Menu *m, int x);
void DisableItem(Menu *m, int x);
void EnableItemCond(Menu *m, int x, int b);
void CheckItem(Menu *m, int x);
void UncheckItem(Menu *m, int x);
void CheckItemCond(Menu *m, int x, int b);
void RenameItem(Menu *m, int x, const char *s);

#endif /* LIB_MENUS */
