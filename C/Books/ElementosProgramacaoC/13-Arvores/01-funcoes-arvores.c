// Compile command: gcc 01-funcoes-arvores.c -c
#include "01-funcoes-arvores.h"


// 1. Funções básicas sobre ARVORES ///////////////////////////////////////////

Tree treenew(Item x)
{
    Tree p = malloc(sizeof(Treenode));
    p->value = x;
    p->sub[left] = p->sub[right] = NULL_TREE;
    return p;
}

Tree treeclr(Tree *s)
{
    return *s = NULL_TREE;
}

Tree treecpy(Tree *s, constTree t)
{
    if (t == NULL_TREE)
        *s = NULL_TREE;
    else
    {
        *s = treenew(t->value);
        treecpy(&(*s)->sub[left], t->sub[left]);
        treecpy(&(*s)->sub[right], t->sub[right]);
    }
    return *s;
}

Tree treecons(Item x, Tree *s, Child c)
{
    Tree p = treenew(x);
    p->sub[c] = *s;
    return *s = p;          // resest *s as root p
}

Tree treestrt(Tree s, Item x)
{
    s->value = x;
    return s;
}

Tree treeswch(Tree s, Tree *t, Child c)
{
    Tree p;
    p = s->sub[c];
    s->sub[c] = *t;
    *t = p;
    return s;
}

Tree treefree(Tree *s)
{
    if (!treenull(treechld(*s, left)))
        treefree(&treechld(*s, left));
    if (!treenull(treechld(*s, right)))
        treefree(&treechld(*s, right));
    return treeclr(s);
}

// 2. Funções utilitárias sobre ARVORES ///////////////////////////////////////

int  treeleaf(constTree s)
{
    return treenull(treechld(s, left)) && treenull(treechld(s, right));
}

int  treesize(constTree s)
{
    return treenull(s) ? 0 :
            1 + treesize(treechld(s, left)) + treesize(treechld(s, right));
}

int  treehght(constTree s)
{
    return treenull(s) ? 0 :
            1 + max(treehght(treechld(s, left)), treehght(treechld(s, right)));
}

int  max(int a, int b)
{
    return a > b ? a : b;
}

int  min(int a, int b)
{
    return a < b ? a : b;
}

void treepre(constTree s, void(*p)(Item))
{
    if (!treenull(s))
    {
        p(s->value);
        treepre(treechld(s, left), p);
        treepre(treechld(s, right), p);
    }
}

void treein(constTree s, void(*p)(Item))
{
    if (!treenull(s))
    {
        treein(treechld(s, left), p);
        p(s->value);
        treein(treechld(s, right), p);
    }
}

void treepost(constTree s, void(*p)(Item))
{
    if (!treenull(s))
    {
        treepost(treechld(s, left), p);
        treepost(treechld(s, right), p);
        p(s->value);
    }
}

// 3. ARVORES de procura //////////////////////////////////////////////////////

Tree treemmbr(Tree s, constItem x, int(*f)(constItem, constItem))
{
    Item r;
    Tree t;
    return treenull(s) ? NULL_TREE :
            f((r = treeroot(s)), x) == 0 ? s :
            (t = treemmbr(treechld(s, left), x, f)) != NULL_TREE ? t :
            treemmbr(treechld(s, right), x, f);
}

Tree treesrch(Tree s, constItem x, int(*f)(constItem, constItem))
{
    Item r;
    while (!treenull(s) && f(r = treeroot(s), x) != 0)
        s = treechld(s, f(x, r) > 0);
    return s;
}

Tree treeins(Tree *s, Item x, int(*f)(constItem, constItem))
{
    if (!*s)
        return treecons(x, s, left);
    else if (f(x, (*s)->value) == 0)
        return *s;
    else
        return treeins((*s)->sub + (f(x, (*s)->value) > 0), x, f);
}

Child boolchld(int value)
{
    return value == 0 ? left : right;
}
