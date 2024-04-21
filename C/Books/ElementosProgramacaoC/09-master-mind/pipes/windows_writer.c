#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define PIPE_READ 0
#define PIPE_WRITE 1

int main() {
    HANDLE pipe_fd[2];

    // Create pipe
    if (!CreatePipe(&pipe_fd[PIPE_READ], &pipe_fd[PIPE_WRITE], NULL, 0)) {
        perror("CreatePipe");
        exit(EXIT_FAILURE);
    }

    // Close read end of pipe
    CloseHandle(pipe_fd[PIPE_READ]);

    // Write data to pipe
    const char* message = "Hello from Program windows_writer";
    DWORD bytesWritten;
    if (!WriteFile(pipe_fd[PIPE_WRITE], message, strlen(message) + 1, &bytesWritten, NULL)) {
        perror("WriteFile");
        exit(EXIT_FAILURE);
    }

    // Close write end of pipe
    CloseHandle(pipe_fd[PIPE_WRITE]);

    return 0;
}
