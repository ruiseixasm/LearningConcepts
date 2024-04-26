#ifndef LIB_DIALOGS
#define LIB_DIALOGS

#include "menus.h"
#include "buttons.h"
#include "string_util.h"

#define CANCEL  '$'
#define INVALID_INTEGER "Invalid integer."
#define OK_243  "OK? "

typedef int (*Fstring)(const char *);   // Validation functions (read only)
typedef int (*Fint)(int);

#endif /* LIB_DIALOGS */
