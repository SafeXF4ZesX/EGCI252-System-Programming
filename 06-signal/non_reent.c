#include <stdio.h>
#include <pthread.h>

int g_var = 1;

int f()
{
    g_var = g_var + 2; //<-PAUSE->
    return g_var;
}

int *g()
{
    printf("g_var = %d\n", f() + 2);
}

int main()
{
    // g();
    pthread_t t1,t2;

    pthread_create(&t1, NULL, g, NULL);
    pthread_create(&t2, NULL, g, NULL);
    pthread_join(&t1,NULL);
    pthread_join(&t2,NULL);
    printf("g() = %d\n", g());
    return 0;
}