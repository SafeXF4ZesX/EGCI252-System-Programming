#include <stdio.h>

int main(void)
{
    FILE *in, *out;

    char buffer[512];
 
    in = fopen("file.in", "r");
    out = fopen("file.out", "w");


    while (fgets(buffer, sizeof(buffer), in) != NULL)
      fputs(buffer, out);
    
    return 0;
}