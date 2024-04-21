/*
 * A program that creates a pipe for communication between its child and itself.
 * From: https://github.com/rst0git/c-pipe-example
 * Compile command: gcc linux_pipe.c -o linux_pipe.out
 */

#include <stdio.h>
#include <stdlib.h>     // needed for exit()
#include <unistd.h>     // needed for pipe()
#include <sys/types.h>

#define DATA "We all know Linux is great... it does infinite loops in 5 seconds"
#define PIPE_READ   0
#define PIPE_WRITE  1

void main(void)
{
    int sockets[2], child;  // sockets[] is just another name for fd[]
    
    /* 
     * Create a pipe and place descriptors for the sockets
     * for the two ends of the pipe. The socket whose index is returned in the
     * low word of the array is opened for reading only, while the socket in the
     * high end is opened only for writing.
     */
    if (pipe(sockets) < 0) {    // Where the bifurcation happens
        perror("opening stream socket pair");
        exit(10);
    }
    
    /* 
     * The parent creates the child with which it will share the pipe.
     * After the fork, both parent's and child's descriptor tables point to the
     * pipe. The child can then use the pipe to send a message to the parent.
     */
    if ((child = fork()) == -1)
        perror("fork");
    
    else if (child) {
        char buf[1024];
        /* This is still the parent. */
        
        /*
         * Close the write socket as it will not be used.
         * This is not reqired but it is a good practice.
         */
        close(sockets[PIPE_WRITE]);
        
        /* Read message from the child. */
        if (read(sockets[PIPE_READ], buf, 1024) < 0)
            perror("reading message");

        /* Print recieved message. */
        printf(">> %s\n", buf);
        
        close(sockets[PIPE_READ]);  /* Close socket. */
        
    } else {
        
        /* This is the child. */
        
        /*
         * Close the write socket as it will not be used.
         * This is not reqired but it is a good practice.
         */
        close(sockets[PIPE_READ]);
        
        /* Writes a message to the parent. */
        if (write(sockets[PIPE_WRITE], DATA, sizeof(DATA)) < 0)
            perror("writing message");
            
        close(sockets[PIPE_WRITE]);  /* Close socket. */
    }
}
