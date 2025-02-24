#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) // reader.c
{
    int n_bytes, fd;
    char buffer[BUFSIZ + 1];
    memset(buffer, '\0', sizeof(buffer));
    sscanf(argv[1], "%d", &fd);     //convert string to integer
    n_bytes = read(fd, buffer, BUFSIZ);
    printf("%d bytes have been read from %d : %s\n", n_bytes, getpid(), buffer);
    exit(EXIT_SUCCESS);
}