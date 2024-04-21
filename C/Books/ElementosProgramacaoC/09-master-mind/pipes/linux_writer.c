// Compile command: gcc linux_writer.c -o linux_writer.out
#include <stdio.h>
#include <stdlib.h>
// On Unix-like systems, the interface defined by unistd.h is typically made up largely of system call wrapper
//     functions such as fork, pipe and I/O primitives (read, write, close, etc.).
#include <unistd.h>

int main() {
    int pipe_fd[2];
    char buffer[100];
    
    // Create pipe
    if (pipe(pipe_fd) == -1) {  // Where the bifurcation happens
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Fork a child process
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // Child process (Reader)
        // Close write end of pipe
        close(pipe_fd[1]);
        
        //// Read data from pipe
        //read(pipe_fd[0], buffer, sizeof(buffer));
        //printf("Received message from parent: %s\n", buffer);
        
        // Close read end of pipe
        close(pipe_fd[0]);
    } else { // Parent process (Writer)
        // Close read end of pipe
        close(pipe_fd[0]);
        
        // Write data to pipe
        printf("Enter a message to send to child: ");
        fgets(buffer, sizeof(buffer), stdin);
        write(pipe_fd[1], buffer, sizeof(buffer));
        
        // Close write end of pipe
        close(pipe_fd[1]);
    }

    return 0;
}
