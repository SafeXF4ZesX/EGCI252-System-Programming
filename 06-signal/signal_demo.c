#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


void my_alarm(int sig)
{
    for (int i = 0; i < 5; i++)
        printf("Alarm!!! \n");
}
int main(void)
{
    int pid;
    printf("Alarm clock is starting…\n");


    /*
    if (pid = fork() == 0)
        {
            sleep(3);   //after 3 secs
            kill(getppid(), SIGALRM);       //kill means sent signal, sent Alarm
            exit(0);
        }
    */


    printf("Waiting for alarm…\n");
    signal(SIGALRM, my_alarm);              //signal tell the system when SIGALRM reach, call my_alarm function aka. how to handle
    alarm(3);
    pause();
    printf("Done!\n");
    exit(0);
}