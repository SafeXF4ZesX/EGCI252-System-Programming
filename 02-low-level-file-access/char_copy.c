#include <stdio.h>

int main(void)
{
    FILE *in, *out;
    char c;

    in = fopen("file.in", "r");
    out = fopen("file.out", "w");

    while ((c = getc(in)) != EOF)
        putc(c, out);

    return 0;
}