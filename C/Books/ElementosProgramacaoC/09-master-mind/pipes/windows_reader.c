#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define PIPE_READ 0
#define PIPE_WRITE 1

int main() {
    HANDLE pipe_fd[2];
    char buffer[100];
    DWORD bytesRead;

    // Create pipe
    if (!CreatePipe(&pipe_fd[PIPE_READ], &pipe_fd[PIPE_WRITE], NULL, 0)) {
        perror("CreatePipe");
        exit(EXIT_FAILURE);
    }

    // Create child process
    PROCESS_INFORMATION pi;
    STARTUPINFO si;
    ZeroMemory(&pi, sizeof(pi));
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    si.hStdOutput = pipe_fd[PIPE_WRITE];
    si.hStdError = pipe_fd[PIPE_WRITE];
    si.dwFlags |= STARTF_USESTDHANDLES;

    if (!CreateProcess(NULL, "windows_writer.exe", NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi)) {
        perror("CreateProcess");
        exit(EXIT_FAILURE);
    }

    // Close unused end of pipe
    CloseHandle(pipe_fd[PIPE_WRITE]);

    printf("Start reading...\n");

    while (1) {
        // Read data from pipe
        if (ReadFile(pipe_fd[PIPE_READ], buffer, sizeof(buffer), &bytesRead, NULL)) {
            printf("Received message from parent: %s\n", buffer);
        }
    }

    // Close read end of pipe
    CloseHandle(pipe_fd[PIPE_READ]);

    // Wait for child process to exit
    WaitForSingleObject(pi.hProcess, INFINITE);

    return 0;
}
