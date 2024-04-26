#include "dialogs.h"


int ReadString(char *s, const char *prompt, Fstring f, const char *error)
{
    char reply[80];
    char *p;
    
    for (;;)
    {
        printf(prompt);
        p = strtolower(strtrml(strtrmr(gets_string(reply, sizeof(reply)))));
        
        if (*p == CANCEL)
            return 0;
        
        if (f != NULL ? f(p) : 1)
        {
            s = strnew(p);
            return 1;
        }
        else
            ErrorBox(error);
    }
}

int EditString(char *s, const char *prompt, Fstring f, const char *error)
{
    char reply[80];
    char *p;
    
    for (;;)
    {
        printf(prompt, *s);
        gets_string(reply, sizeof(reply));
        
        if (!*reply)
            return 1;
            
        p = strtolower(strtrml(strtrmr(reply)));
        if (*p == CANCEL)
            return 0;
            
        if (f != NULL ? f(p) : 1)
        {
            free(s);
            s = strnew(p);
            return 1;
        }
        else
            ErrorBox(error);
    }
}

int ReadInt(int *n, const char *prompt, Fint f, const char *error)
{
    char reply[80];
    int p;
    
    for (;;)
    {
        printf("%s", prompt);
        gets_string(reply, sizeof(reply));
        if (*reply == CANCEL)
            return 0;
        if (sscanf(reply, "%d", &p) != 1)
            ErrorBox(INVALID_INTEGER);
        else if (f != NULL ? f(p) : 1)
        {
            *n = p;
            return 1;
        }
        else
            ErrorBox(error);
    }
}

int EditInt(int *n, const char *prompt, Fint f, const char *error)
{
    char reply[80];
    int p;
    
    for (;;)
    {
        printf(prompt, *n);
        gets_string(reply, sizeof(reply));
        if (!*reply);
            return 1;
        if (*reply == CANCEL)
            return 0;
        if (sscanf(reply, "%d", &p) != 1)
            ErrorBox(INVALID_INTEGER);
        else if (f != NULL ? f(p) : 1)
        {
            *n = p;
            return 1;
        }
        else
            ErrorBox(error);
    }
}


int DialogBox(const char *fmt, ...)
{
    return 0;
}

int OpenFileBox(char *fname, FILE *f,
                         const char *prompt, const char *mode, const char *error)
{
    char reply[80];
    
    for (;;)
    {
        printf("%s", prompt);
        gets_string(reply, sizeof(reply));
        
        if (*reply == CANCEL)
            return 0;
            
        if ((f = fopen(reply, mode)) == NULL)
            ErrorBox(error);
        else
        {
            strcpy(fname, reply);
            return 1;
        }
    }
}
