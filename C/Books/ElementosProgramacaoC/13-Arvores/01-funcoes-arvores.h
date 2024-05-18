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
#define treerroot(s)    ((s)->value)
#define treechld(s, c)  ((s)->sub[c])
Tree treeswch(Tree s, Tree *t, Child c);

// 2. Funções utilitárias sobre ARVORES ///////////////////////////////////////

int  treeleaf(constTree s);
int  treesize(constTree s);
int  treehght(constTree s);
int  max(int a, int b);

// 3. Percursos em ARVORES ////////////////////////////////////////////////////

void treepre(constTree s, void(*p)(Item));
void treein(constTree s, void(*p)(Item));
void treepost(constTree s, void(*p)(Item));

// 4. ARVORES de procura //////////////////////////////////////////////////////

Tree treemmbr(constTree s, constItem x, int(*f)(constItem, constItem));
Tree treesrch(constTree s, constItem x, int(*f)(constItem, constItem));
Tree treeins(Tree *s, Item x, int(*f)(constItem, constItem));

#endif /* FUNC_ARVORES */
