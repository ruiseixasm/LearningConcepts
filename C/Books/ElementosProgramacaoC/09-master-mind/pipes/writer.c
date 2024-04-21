#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>
#define PIPE_READ 0
#define PIPE_WRITE 1
#else
#include <unistd.h>
#endif

int main() {
    int pipe_fd[2];
    char buffer[100];
    
#ifdef _WIN32
    // Create pipe
    if (!CreatePipe(&pipe_fd[PIPE_READ], &pipe_fd[PIPE_WRITE], NULL, 0)) {
        perror("CreatePipe");
        exit(EXIT_FAILURE);
    }
#else
    // Create pipe
    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
#endif

    // Fork a child process
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // Child process (Reader)
#ifdef _WIN32
        // Close write end of pipe
        CloseHandle(pipe_fd[PIPE_WRITE]);

        // Read data from pipe
        DWORD bytesRead;
        if (!ReadFile(pipe_fd[PIPE_READ], buffer, sizeof(buffer), &bytesRead, NULL)) {
            perror("ReadFile");
            exit(EXIT_FAILURE);
        }
        printf("Received message from parent: %s\n", buffer);

        // Close read end of pipe
        CloseHandle(pipe_fd[PIPE_READ]);
#else
        // Close write end of pipe
        close(pipe_fd[1]);

        // Read data from pipe
        read(pipe_fd[0], buffer, sizeof(buffer));
        printf("Received message from parent: %s\n", buffer);

        // Close read end of pipe
        close(pipe_fd[0]);
#endif
    } else { // Parent process (Writer)
#ifndef _WIN32
        // Close read end of pipe
        close(pipe_fd[0]);

        // Write data to pipe
        printf("Enter a message to send to child: ");
        fgets(buffer, sizeof(buffer), stdin);
        write(pipe_fd[1], buffer, sizeof(buffer));

        // Close write end of pipe
        close(pipe_fd[1]);
#endif
    }

    return 0;
}
