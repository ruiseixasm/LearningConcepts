#ifndef FUNC_LISTAS
#define FUNC_LISTAS

#include <stdlib.h>     // defines NULL
#include <string.h>

// void pointers as generic Items
typedef void *LItem;
typedef const void *constLItem;

typedef struct lnode *List; // Apontador
typedef const struct lnode *constList;
typedef struct lnode {
    LItem value;
    List next;
} Listnode;                 // Tipo (Valor)

#define NULL_LIST NULL      // NULL_LIST alias to NULL


// 1. Funções básicas sobre listas ///////////////////////////////////////////

List listcpy(List *s, constList t);                 /* duplicação           */
List listnew(LItem x);                              /* nova linha unitária  */
List listclr(List *s);                              /* limpar a lista       */
List listcons(LItem x, List *s);                    /* acrescentar à cabeça */
List liststhd(List s, LItem x);                     /* modificar a cabeça   */
List listswtl(List s, List *t);                     /* troca a cauda        */

LItem listhead(constList s);                        /* a cabeça             */
List listtail(constList s);                         /* a cauda              */
int  listlen(constList s);                          /* o comprimento        */
int  listnull(constList s);                         /* é vazia?             */

List listfree(List *s);                             /* liberta memória      */

// 2. Funções utilitárias sobre listas ///////////////////////////////////////

List listsuff(List s, int n);                       /* sufixo               */
List listinsx(LItem x, List s, int n);              /* Inserção em posição  */
List listlist(List x, List s, int n);               /* inserção de lista    */
List listrm(List s, int n);                         /* remoção              */
List listsplt(List s, int n, List *t);              /* partição             */
List listfoot(List s);                              /* pé                   */
List listcat(List *s, List t);                      /* concatenação         */

// 3. Funções de busca em listas /////////////////////////////////////////////

List listmmbr(List s, constLItem x);        /* membro de uma lista          */
List listsrch(List s, constLItem x,
        int(*f)(constLItem, constLItem));   /* busca em lista ordenada      */
List listins(List *s, LItem x,
        int(*f)(constLItem, constLItem));   /* inserção em lista ordenada   */
List listentr(List *s, LItem x,
        int(*f)(constLItem, constLItem));   /* idem, sem repetição          */
List listpos(List s, constLItem x,
        int(*f)(constLItem, constLItem));   /* posição de inserção          */

// 4. Funções de comparação //////////////////////////////////////////////////

static int charstrcmp(char *x, char *y);    /* compara strings              */
static int LItemstrcmp(constLItem x, constLItem y);
                                            /* compara LItems como strings  */

// 5. Extra functions from trees chapter /////////////////////////////////////

void listfw(constList s, void(*p)(LItem));  /* moves forward iteratively    */
void listbw(constList s, void(*p)(LItem));  /* moves backward recursively   */


#endif /* FUNC_LISTAS */
