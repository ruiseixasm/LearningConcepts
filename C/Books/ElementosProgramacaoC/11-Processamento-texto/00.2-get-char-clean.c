// Compile command: gcc 00.2-get-char-clean.c -o 00.2-get-char-clean.out

#include <stdio.h>

int main()
{
    long nc = 0;
    long nl = 0;
    int c;
    
    // The EOF marker is a signal that there is no more data to be read from the input stream.
    // It is typically generated by the operating system or the terminal environment when you
    //      indicate the end of input through a special key combination or command,
    //      such as Ctrl+D (on Unix-like systems) or Ctrl+Z (on Windows).
    
    for (; (c = getchar()) != EOF; nc++)    // Not the same as gets()
        if (c == '\n')
            nl++;
    printf("%ld %ld\n", nc, nl);            // Also counts '\n' chars
        
    return 0;
}
