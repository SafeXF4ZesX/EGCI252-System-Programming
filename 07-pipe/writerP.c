#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(void) // writer.c
{
    int n_bytes, pipefd[2], pid;
    char buffer[BUFSIZ + 1], data[] = "12345";
    memset(buffer, '\0', sizeof(buffer));
    if (pipe(pipefd) == 0)
    {
        pid = fork();
        switch (pid)
        {
        case -1:
            fprintf(stderr, "Fork failed!\n");
            break;
        case 0:
            sprintf(buffer, "%d", pipefd[0]);
            execl("readerP", "readerP", buffer, (char *)0);
            exit(EXIT_FAILURE);
        default:
            n_bytes = write(pipefd[1], data, strlen(data));
            printf("%d bytes have been written from %d!\n", n_bytes, getpid());
        }
    }
    wait(NULL);
    exit(EXIT_SUCCESS);
}