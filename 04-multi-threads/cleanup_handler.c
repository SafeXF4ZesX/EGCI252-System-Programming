#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void cleanup(void *arg){
    printf("Thread %d cleaning up\n", (unsigned int)pthread_self());
    free(arg);
    //printf("Cleanup: Releasing resource: %s\n", (char *)arg);
}

void *thread_func(void *arg){
    printf("Thread started.\n");

    int *p = malloc(32);

    // Register cleanup handler
    pthread_cleanup_push(cleanup, p);

    // Simulate some work
    for (int i = 0; i < 5; i++)
    {
        printf("Thread working: %d\n", i);
        sleep(1);
        // Simulate a cancellation point
        pthread_testcancel();
    }

    // Deregister cleanup handler (don't execute it now)
    pthread_cleanup_pop(0);

    printf("Thread finished normally.\n");
    return NULL;
}

int main(){
    pthread_t thread;

    // Create a new thread
    if (pthread_create(&thread, NULL, thread_func, NULL) != 0)
    {
        perror("Failed to create thread");
        return 1;
    }

    // Let the thread run for a bit
    sleep(2);

    // Cancel the thread
    printf("Main: Canceling thread...\n");
    pthread_cancel(thread);

    // Wait for the thread to finish
    pthread_join(thread, NULL);

    printf("Main: Thread joined.\n");
    return 0;
}