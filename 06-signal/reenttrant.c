#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <pthread.h>

int g_var = 1;

int f(void *p)
{
    int *x = (int *) p;
    *x = *x + 2; //<-PAUSE->
    return *x;
}

int *g(void *p)
{
    printf("p = %d\n", f(p) + 2);
}

int main()
{
    // g();
    pthread_t t1,t2;
    int p = 1;

    pthread_create(&t1, NULL, g, &p);
    pthread_create(&t2, NULL, g, &p);
    pthread_join(&t1,NULL);
    pthread_join(&t2,NULL);
    printf("g() = %d\n", g(p));
    return 0;
}