// Compile command: gcc 02.2-funcoes-sobre-listas-void.c -c
#include "02.2-funcoes-sobre-listas-void.h"


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

List listfree(List *s)                              /* liberta memória      */
{
    for (List p = *s; !listnull(p); p = p->next)
        free(p);        // p is a pointer to a Listnode (avoids memory leak)
    return listclr(s);
}

// 2. Funções utilitárias sobre listas ///////////////////////////////////////

List listsuff(List s, int n)                        /* sufixo               */
{
    while (--n)
        s = listtail(s);
    return s;
}

List listinsx(Item x, List s, int n)                /* Inserçaõ em posição  */
{
    List p = listnew(x);
    List q = listsuff(s, n);
    listswtl(q, &p);
    return listswtl(listtail(q), &p);
}

List listlist(List x, List s, int n)                /* inserção de lista    */
{
    List p = x;
    listswtl(listsuff(s, n), &p);
    return listswtl(listfoot(x), &p);
}

List listrm(List s, int n)                          /* remoção              */
{
    List left = listsuff(s, n - 1);
    List right = left->next;
    left->next = right->next;   // bypasses the node to be deleted (free)
    right->next = NULL_LIST;    // makes it a single node list (right)
    listfree(&right);           // frees allocated memory with malloc
    return left;
}

List listsplt(List s, int n, List *t)               /* partição             */
{
    //                              returns t instead of *t
    return listswtl(listsuff(s, n), (listclr(t), t));
}

List listfoot(List s)                               /* pé                   */
{
    while (!listnull(listtail(s)))
        s = listtail(s);
    return s;
}

List listcat(List *s, List t)                       /* concatenação         */
{
    if (listnull(*s))
        *s = t;     // because of this line it needs to be passed by pointer
    else
        listswtl(listfoot(*s), &t);
    return *s;
}

// 3. Funções de busca em listas /////////////////////////////////////////////

List listmmbr(List s, constItem x)          /* membro de uma lista          */
{
    while (s && (x != s->value))
        s = s->next;
    return s;
}

List listsrch(List s, constItem x,
        int(*f)(constItem, constItem))      /* busca em lista ordenada      */
{
    while (!listnull(s) && f(x, listhead(s)) > 0)
        s = listtail(s);
    return f(x, listhead(s)) ? NULL_LIST : s;
}

List listins(List *s, Item x,
        int(*f)(constItem, constItem))      /* inserção em lista ordenada   */
{
    List p, q;
    if (listnull(*s) || f(x, listhead(*s)) < 0)
        return listcons(x, s);
    else
    {
        listswtl(q = listpos(*s, x, f), (p = listnew(x), &p));
        return listswtl(listtail(q), &p);
    }
}

List listentr(List *s, Item x,
        int(*f)(constItem, constItem))      /* idem, sem repetição          */
{
    List p, q;
    if (listnull(*s) || f(x, listhead(*s)) < 0)
        return listcons(x, s);
    else if (f(x, listhead(q = listpos(*s, x, f))) == 0)
        return NULL_LIST;   // Não adicciona se já existe na lista
    else
    {
        listswtl(q, (p = listnew(x), &p));
        return listswtl(listtail(q), &p);
    }
}

List listpos(List s, constItem x,
        int(*f)(constItem, constItem))      /* posição de inserção          */
{
    List p;
    //                   next                 value
    while (!listnull(p = listtail(s)) && f(x, listhead(p)) >= 0)
        s = p;
    return s;
}

// 4. Funções de comparação //////////////////////////////////////////////////

static int charstrcmp(char *x, char *y)     /* compara strings              */
{
    return strcmp(x, y);
}

static int itemstrcmp(constItem x, constItem y)
                                            /* compara Items como strings   */
{   //                 pointers casting is always implicitly done (guaranteed)
    return charstrcmp((char *)x, (char *)y);
}

// 5. Extra functions from trees chapter /////////////////////////////////////

void listfw(List s, void(*p)(Item))         /* moves forward iteratively    */
{
    while (!listnull(s))
    {
        p(listhead(s));
        s = listtail(s);
    }
}

void listbw(List s, void(*p)(Item))         /* moves backward recursively   */
{
    if (!listnull(s))
    {
        listbw(listtail(s), p);
        p(listhead(s));
    }
}
