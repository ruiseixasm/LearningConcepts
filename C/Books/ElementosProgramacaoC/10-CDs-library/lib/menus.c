#include "menus.h"

static void DisplayMenu(const Menu *m)
{
    printf("%s\n", m->title);
    for (int i = 0; i < m->n_Items; i++)
    {
        if (m->items[i].enabled)
            printf("(%2d)", i + 1);
        else
            printf("(  )");
        printf(" %s%s\n", m->items[i].name, m->items[i].checked ? " +" : "");
    }
    printf("--> ");
}

int MenuSelect(const Menu *m)
{
    char reply[80];
    int i, n;
    const MenuItem *p;

    for (;;)
    {
        DisplayMenu(m);
        gets_string(reply, sizeof(reply));  // same as gets(reply)

        if (!*reply)
            return 0;
            
        else if (isdigit(*reply))
            if ((n = atoi(reply)) <= m->n_Items && m->items[n - 1].enabled)
                return n;
            else
                printf("\a");
        else
        {
            for (i = 1, p = m->items; i <= m->n_Items; i++, p++)
                if (p->enabled && p->name == strstr(p->name, reply))
                    return i;
            printf("\a");
        }
    }
}


void CreateMenu(Menu *m, const char *t, const char *s)
{
    MenuItem *p;
    char *u;
    m->title = strnew(t);
    
    for (p = m->items; *s; s = u + 1, p++)
    {
        p->name = strnewn(s, (u = strchr(s, ';')) - s);
        p->enabled = 1; // true
        p->checked = 0; // false
    }
    m->n_Items = p - m->items;
}

void AppendItem(Menu *m, const char *s)
{
    MenuItem *p;
    p = m->items + m->n_Items++;
    p->name = strnew(s);
    p->enabled = 1; // true
    p->checked = 0; // false
}

void EnableItem(Menu *m, int x)
{
    m->items[x - 1].enabled = 1;    // true
}

void DisableItem(Menu *m, int x)
{
    m->items[x - 1].enabled = 0;    // false
}

void EnableItemCond(Menu *m, int x, int b)
{
    if (b)
        EnableItem(m, x);
    else
        DisableItem(m, x);
}

void CheckItem(Menu *m, int x)
{
    m->items[x - 1].checked = 1;    // true
}

void UncheckItem(Menu *m, int x)
{
    m->items[x - 1].checked = 0;    // false
}

void CheckItemCond(Menu *m, int x, int b)
{
    if (b)
        CheckItem(m, x);
    else
        UncheckItem(m, x);
}

void RenameItem(Menu *m, int x, const char *s)
{
    //char **p = &(m->items[x - 1].name);
    //free(*p);
    //*p = strnew(s);
    
    free(m->items[x - 1].name);
    m->items[x - 1].name = strnew(s);
}
