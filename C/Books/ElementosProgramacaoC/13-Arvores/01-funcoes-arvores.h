#ifndef FUNC_ARVORES
#define FUNC_ARVORES

#include <stdlib.h>     // defines NULL
#include <string.h>

// void pointers as generic Items
typedef void *TItem;
typedef const void *constTItem;

typedef struct tnode *Tree; // Apontador
typedef const struct tnode *constTree;
typedef struct tnode {
    TItem value;
    Tree sub[2];
} Treenode;
typedef enum {left, right} Child;

#define NULL_TREE NULL      // NULL_TREE alias to NULL


// 1. Funções básicas sobre ARVORES ///////////////////////////////////////////

Tree treenew(TItem x);
Tree treeclr(Tree *s);
Tree treecpy(Tree *s, constTree t);
Tree treecons(TItem x, Tree *s, Child c);
Tree treestrt(Tree s, TItem x);
//int  treenull(constTree s);
//Tree treeroot(constTree s);
//Tree treechld(constTree s, Child c);
#define treenull(s)     (!(s))
#define treeroot(s)     ((s)->value)
#define treechld(s, c)  ((s)->sub[c])
Tree treeswch(Tree s, Tree *t, Child c);

Tree treefree(Tree *s);

// 2. Funções utilitárias sobre ARVORES ///////////////////////////////////////

int  treeleaf(constTree s);
int  treesize(constTree s);
int  treehght(constTree s);

int  max(int a, int b);
int  min(int a, int b);

void treepre(constTree s, void(*p)(TItem));
void treein(constTree s, void(*p)(TItem));
void treepost(constTree s, void(*p)(TItem));

// 3. ARVORES de procura //////////////////////////////////////////////////////

Tree treemmbr(Tree s, constTItem x, int(*f)(constTItem, constTItem));
Tree treesrch(Tree s, constTItem x, int(*f)(constTItem, constTItem));
Tree treeins(Tree *s, TItem x, int(*f)(constTItem, constTItem));
Child boolchld(int value);

#endif /* FUNC_ARVORES */
