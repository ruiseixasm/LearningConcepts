#include "dialogs.h"


int ReadString(char **s, const char *prompt, Fstring f, const char *error)
{
    char reply[80];
    char *p;
    
    for (;;)
    {
        printf("%s", prompt);
        p = strtolower(strtrml(strtrmr(gets_string(reply, sizeof(reply)))));
        
        if (*p == CANCEL)
            return 0;
        
        if (f != NULL ? f(p) : 1)
        {
            *s = strnew(p);
            return 1;
        }
        else
            ErrorBox(error);
    }
}

int EditString(char **s, const char *prompt, Fstring f, const char *error)
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
            *s = strnew(p);
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
    int cancelled = 0;  // false
    int count = 0;
    va_list ap;
    const char *p;
    
    char **s_ref;
    Fstring fstring;
    char *prompt;
    char *error;
    
    int *n_ref;
    Fint fint;
    Menu *m_ref;
    int m_choice;
    
    int d_item; // Boolean
    
    va_start(ap, fmt);
    
    for (p = fmt; *p && !cancelled; p++)
    {
        if (*p != '%')
        {
            putchar(*p);
            continue;
        }
        switch (*++p)
        {
            case 'd':
            case 'D':
                n_ref = va_arg(ap, int *);
                prompt = va_arg(ap, char *);
                fint = va_arg(ap, Fint);
                error = va_arg(ap, char *);
                if ((*p == 'd' ? ReadInt : EditInt)
                    (n_ref, prompt, fint, error))
                    count++;
                else
                    cancelled = 1;  // true
                break;
                
            case 's':
            case 'S':
                s_ref = va_arg(ap, char **);
                prompt = va_arg(ap, char *);
                fstring = va_arg(ap, Fstring);
                error = va_arg(ap, char *);
                
                if ((*p == 's' ? ReadString : EditString)
                    (s_ref, prompt, fstring, error))
                    count++;
                else
                    cancelled = 1;  // true
                break;
                
            case 'm':
            case 'M':
                n_ref = va_arg(ap, int *);
                m_ref = va_arg(ap, Menu *);
                CheckItem(m_ref, d_item = *p == 'm' ? 1 : *n_ref);
                *n_ref = (m_choice = MenuSelect(m_ref)) ? m_choice : d_item;
                UncheckItem(m_ref, d_item);
                count++;
                break;
            
            default:
                break;
        }
    }
    
    va_end(ap);
    return !cancelled && NoYesBox(OK_Q) ? count : 0;
}

int OpenFileBox(char *fname, FILE **f,
                         const char *prompt, const char *mode, const char *error)
{
    char reply[80];
    
    for (;;)
    {
        printf("%s", prompt);
        gets_string(reply, sizeof(reply));
        
        if (*reply == CANCEL)
            return 0;
            
        if ((*f = fopen(reply, mode)) == NULL)
            ErrorBox(error);
        else
        {
            strcpy(fname, reply);
            return 1;
        }
    }
}
