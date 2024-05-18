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
} Treenode;                 // Tipo (Valor)

#define NULL_TREE NULL      // NULL_TREE alias to NULL


// 1. Funções básicas sobre ARVORES ///////////////////////////////////////////





#endif /* FUNC_ARVORES */
