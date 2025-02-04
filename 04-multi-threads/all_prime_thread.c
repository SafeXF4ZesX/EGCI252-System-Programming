#include <pthread.h>
#include <stdio.h>

// Compute successive prime numbers (very inefficiently).
// Return the Nth prime number, where N is the value pointed to by *ARG.

void *findPrime(void *arg)
{
    int candidate = 2, n = *((int *)arg);
    while (1)
    {
        int factor, is_prime = 1;
        /* Test primality by successive division. */
        for (factor = 2; factor < candidate; ++factor)
            if (candidate % factor == 0)
            {
                is_prime = 0;
                break;
            }
        /* Is this the prime number we’re looking for? */
        if (is_prime)
        {
            if (--n == 0)
                /* Return the desired prime number as the thread return value. */
                return (void *)candidate;
        }
        ++candidate;
    }
    return NULL;
}

struct char_print_parms{
    char number;
    int count;
};

void *char_print(void *parameters){
    struct char_print_parms *p = (struct char_print_parms *) parameters;
    int i;
    for (i=0 ; i<p->count ; i++){
        fputc(p->number, stdout);
    }
    return NULL;

}


int main()
{
    pthread_t thread_1, thread_2, thread_3, thread_4, thread_5;
    int prime;
    struct char_print_parms thread1_args;
    struct char_print_parms thread2_args;
    struct char_print_parms thread3_args;
    struct char_print_parms thread4_args;
    struct char_print_parms thread5_args;

    /* Start the computing thread, up to the 5,133th prime number. */
    thread1_args.number = 'x' ;
    thread1_args.count = 50000;
    pthread_create(&thread_1, NULL, &findPrime, &thread1_args);
    
    /* Do some other work here... */
    /* Wait for the prime number thread to complete, and get the result. */
    pthread_join(thread_1, NULL);
    
    
    return 0;
}