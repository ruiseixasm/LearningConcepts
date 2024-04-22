#include "items.h"


void BuildItem(Item *x, int b, int t, const Disk *d)
{
    x->label    = b;
    x->deleted  = t;
    x->disk     = *d;
}

void MarkDeleted(Item *t)
{
    t->deleted  = true;
}

void MarkUndeleted(Item *t)
{
    t->deleted  = false;
}
