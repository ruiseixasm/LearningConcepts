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
    Tree p = malloc(sizeof(Treenode));
    p->value = x;
    p->sub[c] = *s;
    p->sub[!c] = NULL_TREE; // complementar sub
    return *s = p;
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

// 3. Percursos em ARVORES ////////////////////////////////////////////////////



// 4. ARVORES de procura //////////////////////////////////////////////////////

