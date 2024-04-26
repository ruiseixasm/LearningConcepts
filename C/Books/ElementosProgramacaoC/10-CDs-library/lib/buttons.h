#ifndef LIB_BUTTONS
#define LIB_BUTTONS

#include <stdio.h>
#include <ctype.h>
#include "utils.h"

int ButtonSelect(const char *s, const char *b);
static void DisplayButtons(const char *b);
static int ButtonListSelect(const char *b);

#define YES_NO  "Yes;No;"
#define NO_YES  "No;Yes;"

int YesNoBox(const char *s);
int NoYesBox(const char *s);

#define OK      "OK;"

void MessageBox(const char *s);

#define ERROR   "ERROR: "

void ErrorBox(const char *s);

#endif /* LIB_BUTTONS */
