#ifndef FUNC_LISTAS
#define FUNC_LISTAS

typedef int Item;
//typedef char *Item;

// Funções básicas sobre listas

List listcpy(List *s, const List t);    /* duplicação           */
List listnew(const Item x);             /* nova linha unitária  */
List listclr(List *s);                  /* limpar a lista       */





#endif /* FUNC_LISTAS */
