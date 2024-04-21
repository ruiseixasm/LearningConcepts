/*****************************************************************************
 Excerpt from "Linux Programmer's Guide - Chapter 6"
 (C)opyright 1994-1995, Scott Burkett
 ***************************************************************************** 
 MODULE: pipe.c
 *****************************************************************************/

// Compile command: gcc pipe.c -o pipe.out

#include <stdio.h>
#include <unistd.h>     // needed for pipe()
#include <sys/types.h>
#include <stdlib.h>     // needed for exit()
#include <string.h>     // needed for strlen()

#define PIPE_READ   0
#define PIPE_WRITE  1

int main(void)
{
        int     fd[2], nbytes;
        pid_t   childpid;
        char    string[] = "Hello, world!\n";
        char    readbuffer[80];

        pipe(fd);       // Where the bifurcation takes place parent (id > 0) + child (id == 0)
        
        if((childpid = fork()) == -1)
        {
                perror("fork");
                exit(1);
        }

        if(childpid == 0)   // child - Writes into pipe
        {
                /* Child process closes up input side of pipe */
                close(fd[PIPE_READ]);

                /* Send "string" through the output side of pipe */
                write(fd[PIPE_WRITE], string, (strlen(string)+1));
                exit(0);
        }
        else                // parent - Reads from pipe
        {
                /* Parent process closes up output side of pipe */
                close(fd[PIPE_WRITE]);

                /* Read in a string from the pipe */
                nbytes = read(fd[PIPE_READ], readbuffer, sizeof(readbuffer));
                printf("Received string: %s", readbuffer);
        }
        
        return(0);
}
