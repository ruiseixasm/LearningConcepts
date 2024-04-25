#ifndef LIB_MENUS
#define LIB_MENUS

#include <stdio.h>
#include <ctype.h>  // nedded for isdigit()
#include <stdlib.h> // needed for atoi(), malloc(), calloc() and free()
#include "utils.h"  // needed for read_input()

#define MAX_MENU_ITEMS  16

typedef struct {
    char *items[MAX_MENU_ITEMS];
    int n_Items;
} Menu;

static void DisplayMenu(const Menu *m);
int MenuSelect(const Menu *m);
void CreateMenu(Menu *m, const char *s);
void EnableItem(Menu *m, int x);
void DisableItem(Menu *m, int x);
void EnableItemCond(Menu *m, int x, int b);


#endif /* LIB_MENUS */
