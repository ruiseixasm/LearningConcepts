#ifndef FUNC_LISTAS
#define FUNC_LISTAS

#include <stdlib.h>     // defines NULL

//typedef int Item;
typedef char *Item;
typedef const char *constItem;

// 1. Funções básicas sobre listas ///////////////////////////////////////////

typedef struct lnode *List; // Apontador
typedef const struct lnode *constList;
typedef struct lnode {
    Item value;
    List next;
} Listnode;                 // Tipo (Valor)

#define NULL_LIST NULL      // NULL_LIST alias to NULL

List listcpy(List *s, constList t);                 /* duplicação           */
List listnew(Item x);                               /* nova linha unitária  */
List listclr(List *s);                              /* limpar a lista       */
List listcons(Item x, List *s);                     /* acrescentar à cabeça */
List liststhd(List s, Item x);                      /* modificar a cabeça   */
List listswtl(List s, List *t);                     /* troca a cauda        */

Item listhead(constList s);                         /* a cabeça             */
List listtail(constList s);                         /* a cauda              */
int  listlen(constList s);                          /* o comprimento        */
int  listnull(constList s);                         /* é vazia?             */

// 2. Funções utilitárias sobre listas ///////////////////////////////////////

//List listsuff(List s, int n);                       /* sufixo               */
//List listinsx(const Item x, List s, int n);         /* Inserçaõ em posição  */
//List listlist(const Listnode *x, List *s, int n);   /* inserção de lista    */
//List listrm(List s, int n);                         /* remoção              */
//List listsplt(const Listnode *x, int n, List *s);   /* partição             */
//List listfoot(const Listnode *x);                   /* pé                   */
//List listcat(List *s, const Listnode *t);           /* concatenação         */

// 3. Funções de busca em listas /////////////////////////////////////////////

//List listmmbr(const Listnode *s, int n);    /* membro de uma lista          */
//List listsrch(const Listnode *s, int n);    /* busca em lista ordenada      */
//List listins(List *s, int n);               /* inserção em lista ordenada   */
//List listentr(List *s, int n);              /* idem, sem repetição          */


#endif /* FUNC_LISTAS */
