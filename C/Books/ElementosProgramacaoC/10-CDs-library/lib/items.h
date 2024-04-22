#ifndef LIB_ITEMS
#define LIB_ITEMS

#include "disks.h"

typedef struct {
    short label;
    short deleted;
    Disk disk;
} Item;

void BuildItem(Item *x, int b, int t, const Disk *d);
void MarkDeleted(Item *t);
void MarkUndeleted(Item *t);

#endif /* LIB_ITEMS */
