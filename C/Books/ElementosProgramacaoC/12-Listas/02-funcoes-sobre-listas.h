#ifndef FUNC_LISTAS
#define FUNC_LISTAS

typedef int Item;
//typedef char *Item;

// 1. Funções básicas sobre listas ///////////////////////////////////////////

typedef struct lnode *List; // Apontador
typedef struct lnode {
    Item value;
    List next;
} Listnode;                 // Tipo (Valor)

#define NULL_LIST NULL      // NULL_LIST alias to NULL

List listcpy(List *s, const Listnode *t);           /* duplicação           */
List listnew(const Item x);                         /* nova linha unitária  */
List listclr(List *s);                              /* limpar a lista       */
List listcons(const Item x, List *s);               /* acrescentar à cabeça */
List liststhd(List *s, const Item);                 /* modificar a cabeça   */

Item listhead(const List *s);                       /* a cabeça             */
List listtail(const List *s);                       /* a cauda              */
int  listlen(const List *s);                        /* o comprimento        */
int  listnull(const List *s);                       /* é vazia?             */

// 2. Funções utilitárias sobre listas ///////////////////////////////////////

List listsuff(List s, int n);                       /* sufixo               */
List listinsx(const Item x, List s, int n);         /* Inserçaõ em posição  */
List listlist(const Listnode *x, List *s, int n);   /* inserção de lista    */
List listrm(List s, int n);                         /* remoção              */
List listsplt(const Listnode *x, int n, List *s);   /* partição             */
List listfoot(const Listnode *x);                   /* pé                   */
List listcat(List *s, const Listnode *t);           /* concatenação         */

// 3. Funções de busca em listas /////////////////////////////////////////////

List listmmbr(const Listnode *s, int n);    /* membro de uma lista          */
List listsrch(const Listnode *s, int n);    /* busca em lista ordenada      */
List listins(List *s, int n);               /* inserção em lista ordenada   */
List listentr(List *s, int n);              /* idem, sem repetição          */


#endif /* FUNC_LISTAS */
