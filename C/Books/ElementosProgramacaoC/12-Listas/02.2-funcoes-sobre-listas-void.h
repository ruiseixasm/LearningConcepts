#ifndef FUNC_LISTAS
#define FUNC_LISTAS

#include <stdlib.h>     // defines NULL
#include <string.h>

// void pointers as generic Items
typedef void *Item;
typedef const void *constItem;

typedef struct lnode *List; // Apontador
typedef const struct lnode *constList;
typedef struct lnode {
    Item value;
    List next;
} Listnode;                 // Tipo (Valor)

#define NULL_LIST NULL      // NULL_LIST alias to NULL


// 1. Funções básicas sobre listas ///////////////////////////////////////////

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

List listfree(List *s);                             /* liberta memória      */

// 2. Funções utilitárias sobre listas ///////////////////////////////////////

List listsuff(List s, int n);                       /* sufixo               */
List listinsx(Item x, List s, int n);               /* Inserçaõ em posição  */
List listlist(List x, List s, int n);               /* inserção de lista    */
List listrm(List s, int n);                         /* remoção              */
List listsplt(List s, int n, List *t);              /* partição             */
List listfoot(List s);                              /* pé                   */
List listcat(List *s, List t);                      /* concatenação         */

// 3. Funções de busca em listas /////////////////////////////////////////////

List listmmbr(List s, constItem x,
        int(*f)(constItem, constItem));     /* membro de uma lista          */
List listsrch(List s, constItem x,
        int(*f)(constItem, constItem));     /* busca em lista ordenada      */
List listins(List *s, Item x,
        int(*f)(constItem, constItem));     /* inserção em lista ordenada   */
List listentr(List *s, Item x,
        int(*f)(constItem, constItem));     /* idem, sem repetição          */
List listpos(List s, constItem x,
        int(*f)(constItem, constItem));     /* posição de inserção          */

// 4. Funções de comparação //////////////////////////////////////////////////

static int charstrcmp(char *x, char *y);    /* compara strings              */
static int itemstrcmp(constItem x, constItem y);
                                            /* compara Items como strings   */

// 5. Extra functions from trees chapter /////////////////////////////////////

void listfw(constList s, void(*p)(Item));   /* moves forward iteratively    */
void listbw(constList s, void(*p)(Item));   /* moves backward recursively   */


#endif /* FUNC_LISTAS */
