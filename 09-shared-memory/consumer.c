#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define MEM_SIZE 4096

struct shm_st
{
    int written;
    char data[BUFSIZ];
};

int main()
{
    int running = 1, shmID;
    void *sh_mem = NULL;
    struct shm_st *sh_area;
    key_t key;
    srand((unsigned int)getpid());
    key = ftok("/home/runner/", 1234);
    shmID = shmget((key_t) key, MEM_SIZE,
                   0666 | IPC_CREAT);
    if (shmID == -1)
    {
        fprintf(stderr, "shmget failed\n");
        exit(EXIT_FAILURE);
    }
    sh_mem = shmat(shmID, NULL, 0);
    if (sh_mem == (void *)-1)
    {
        fprintf(stderr, "shmat failed\n");
        exit(EXIT_FAILURE);
    }
    printf("Memory attached at %X\n", sh_mem);
    sh_area = (struct shm_st *)sh_mem;
    sh_area->written = 0;

    while (running)
    {
        if (sh_area->written)
        {
            printf("Data written in shared memory: %s\n", sh_area->data);
            sh_area->written = 0;
            if (strncmp(sh_area->data, "end", 3) == 0)
                running = 0;
        }
        //sleep(rand() % 4);
        sleep(1);
    }
    if (shmdt(sh_mem) == -1 || shmctl(shmID, IPC_RMID, 0) == -1)
    {
        fprintf(stderr, "shmdt or shmctl failed\n");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}