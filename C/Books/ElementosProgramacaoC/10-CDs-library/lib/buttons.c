#include "buttons.h"

int ButtonSelect(const char *s, const char *b)
{
    printf("%s", s);
    DisplayButtons(b);
    return ButtonListSelect(b);
}

static void DisplayButtons(const char *b)
{
    const char *s, *t;
    int n = 0;
    printf("<");
    for (s = b; *s; s = t + 1)
        if ((t = strchr(s, ';')) != s)
            printf("%s%.*s", n++ ? ", " : "", (int)(t - s), s);
    printf(">");
}

static int ButtonListSelect(const char *b)
{
    char reply[80];
    const char *s;
    int i;
    gets_string(reply, sizeof(reply));
    
    if (!*reply)
        return 1;
        
    *reply = tolower(*reply);
    
    for (i = 1, s = b; *s; i++, s = strchr(s, ';') + 1)
        if (*reply == tolower(*s))
            return i;
    return 1;
}

int YesNoBox(const char *s)
{
    return ButtonSelect(s, YES_NO) == 1;
}

int NoYesBox(const char *s)
{
    return ButtonSelect(s, NO_YES) == 2;
}

void MessageBox(const char *s)
{
    ButtonSelect(s, OK);
}

void ErrorBox(const char *s)
{
    char error[80];
    MessageBox(strcat(strcpy(error, ERROR), s));
}
