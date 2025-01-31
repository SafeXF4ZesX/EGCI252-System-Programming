#include <stdio.h>
#include <unistd.h>
int main()
{
    pid_t pid = fork();
    printf("Process ID : % d\n", (int)pid);
    if (pid == 0)
        execl("./ print", "print", "1", "10", NULL);
    else
        execl("./ print", "print", "2", "20", NULL);
}