// Compile command: gcc 02-funcoes-sobre-listas.c -c
#include "02-funcoes-sobre-listas.h"


// 1. Funções básicas sobre listas ///////////////////////////////////////////

List listcpy(List *s, constList t)                  /* duplicação           */
{
    List p;
    if (t == NULL_LIST)
        *s = NULL_LIST;
    else
    {
        *s = listnew(t->value);
        p = *s;
        t = t->next;
        while (t != NULL_LIST)
        {
            p->next = listnew(t->value);
            p = p->next;
            t = t->next;
        }
    }
    return *s;
}

List listnew(Item x)                                /* nova linha unitária  */
{
    List p = (List)malloc(sizeof(Listnode));
    p->value = x;
    p->next = NULL_LIST;
    return p;
}

List listclr(List *s)                               /* limpar a lista       */
{
    return *s = NULL_LIST;
}

List listcons(Item x, List *s)                      /* acrescentar à cabeça */
{
    List p = listnew(x);
    p->next = *s;
    return *s = p;
}

List liststhd(List s, Item x)                       /* modificar a cabeça   */
{
    s->value = x;
}

List listswtl(List s, List *t)                      /* troca a cauda        */
{
    List p;
    p = s->next;
    s->next = *t;
    *t = p;
    return s;
}

Item listhead(constList s)                          /* a cabeça             */
{
    return s->value;
}

List listtail(constList s)                          /* a cauda              */
{
    return s->next;
}

int  listlen(constList s)                           /* o comprimento        */
{
    int n;
    for (n = 0; s != NULL_LIST; n++)
        s = s->next;
    return n;
}

int  listnull(constList s)                          /* é vazia?             */
{
    return s == NULL_LIST;
}
