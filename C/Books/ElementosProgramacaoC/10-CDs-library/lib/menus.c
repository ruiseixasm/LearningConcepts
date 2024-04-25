#include "menus.h"

static void DisplayMenu(const Menu *m)
{
    for (int i = 0; i < m->n_Items; i++)
        printf("(%2d) %s\n", i + 1, m->items[i]);
    printf("--> ");
}
int MenuSelect(const Menu *m)
{
    char reply[80];
    int n;

    for (;;)
    {
        DisplayMenu(m);
        read_input(reply, sizeof(reply));

        if (!*reply)
            return 0;
        else if (isdigit(*reply) &&
                (n = atoi(reply)) <= m->n_Items)
            return n;
        else
            printf("\a");
    }
}
void CreateMenu(Menu *m, const char *s)
{
    
}
void EnableItem(Menu *m, int x)
{
    
}
void DisableItem(Menu *m, int x)
{
    
}
void EnableItemCond(Menu *m, int x, int b)
{

}
