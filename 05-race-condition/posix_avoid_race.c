#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <asm-generic/fcntl.h>

static void sig_usr(int);

static void sig_usr(int signo){
    if (signo == SIGUSR1)
        printf("received SIGUSR1\n");
    else if (signo == SIGUSR2)
        printf("received SIGUSR2\n");
    else printf("error");
}

int main(){
    pid_t pid;
    
    printf("fork program starting\n");
    pid = fork();
    switch (pid)
    {
    case -1:
        exit(1);
    case 0:
        
        kill(getppid(), SIGUSR1);
        break;
    default:
        
        kill(pid, SIGUSR2);
        break;
    }

    signal(SIGUSR1, sig_usr);
    signal(SIGUSR2, sig_usr);

    return 0;
}