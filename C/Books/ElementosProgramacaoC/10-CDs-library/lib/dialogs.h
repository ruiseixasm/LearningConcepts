#ifndef LIB_DIALOGS
#define LIB_DIALOGS

#include "menus.h"
#include "buttons.h"
#include "string_util.h"

#define CANCEL  '$'
#define INVALID_INTEGER "Invalid integer."
#define OK_Q  "OK? "    // OK already defined in buttons.h

typedef int (*Fstring)(const char *);   // Validation functions (read only)
typedef int (*Fint)(int);

int ReadString(char *s, const char *prompt, Fstring f, const char *error);
int EditString(char *s, const char *prompt, Fstring f, const char *error);
int ReadInt(int *n, const char *prompt, Fint f, const char *error);
int EditInt(int *n, const char *prompt, Fint f, const char *error);

int DialogBox(const char *fmt, ...);
int OpenFileBox(char *fname, FILE *f,
                         const char *prompt, const char *mode, const char *error);

#endif /* LIB_DIALOGS */
