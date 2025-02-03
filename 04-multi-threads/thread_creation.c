#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

/* Prints Xs to stderr. */
void *print_Xs(void *unused)
{
    int n;
    for (n = 100; n > 0; n--)
    {
        fputc('X', stderr);
        usleep(1);
    }
    return NULL;
}

/* Prints Ys to stderr. */
void *print_Ys(void *unused)
{
    int n;
    for (n = 100; n > 0; n--)
    {
        fputc('Y', stderr);
        usleep(1);
    }
    return NULL;
}

int main()
{
    int n;
    pthread_t thread_id1, thread_id2;
    /* Create a new thread. The new thread will run the print_xs function. */
    pthread_create(&thread_id1, NULL, &print_Xs, NULL);
    /* Create a new thread. The new thread will run the print_ys function. */
    pthread_create(&thread_id2, NULL, &print_Ys, NULL);
    /* Print Zs to stderr. */
    for (n = 100; n > 0; n--)
    {
        fputc('Z', stderr); 
        usleep(1);
    }

    //make others thread wait to join
    pthread_join(thread_id1, NULL);
    pthread_join(thread_id2, NULL);

    return 0;
}