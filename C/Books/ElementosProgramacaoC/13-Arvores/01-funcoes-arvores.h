#ifndef FUNC_ARVORES
#define FUNC_ARVORES

#include <stdlib.h>     // defines NULL
#include <string.h>

// void pointers as generic Items
typedef void *Item;
typedef const void *constItem;

typedef struct tnode *Tree; // Apontador
typedef const struct tnode *constTree;
typedef struct tnode {
    Item value;
    Tree sub[2];
} Treenode;
typedef enum {left, right} Child;

#define NULL_TREE NULL      // NULL_TREE alias to NULL


// 1. Funções básicas sobre ARVORES ///////////////////////////////////////////

Tree treenew(Item x);
Tree treeclr(Tree *s);
Tree treecpy(Tree *s, constTree t);
Tree treecons(Item x, Tree *s, Child c);
Tree treestrt(Tree s, Item x);
//int  treenull(constTree s);
//Tree treeroot(constTree s);
//Tree treechld(constTree s, Child c);
#define treenull(s)     (!(s))
#define treeroot(s)     ((s)->value)
#define treechld(s, c)  ((s)->sub[c])
Tree treeswch(Tree s, Tree *t, Child c);

// 2. Funções utilitárias sobre ARVORES ///////////////////////////////////////

int  treeleaf(constTree s);
int  treesize(constTree s);
int  treehght(constTree s);

int  max(int a, int b);
int  min(int a, int b);

void treepre(constTree s, void(*p)(Item));
void treein(constTree s, void(*p)(Item));
void treepost(constTree s, void(*p)(Item));

// 3. ARVORES de procura //////////////////////////////////////////////////////

Tree treemmbr(Tree s, constItem x, int(*f)(constItem, constItem));
Tree treesrch(Tree s, constItem x, int(*f)(constItem, constItem));
Tree treeins(Tree *s, Item x, int(*f)(constItem, constItem));
Child boolchld(int value);

#endif /* FUNC_ARVORES */
