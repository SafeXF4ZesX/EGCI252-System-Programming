#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    printf("Real UID = %d, Eff UID = %d\n ",
                     getuid(),
           geteuid());
    return 0;
}