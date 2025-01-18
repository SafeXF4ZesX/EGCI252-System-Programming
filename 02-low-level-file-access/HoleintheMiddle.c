// Pattadon Pimai 6581007
// Chayuthwarat Tansthitaya 6581125
// Siriwat Ittisompiboon 6581098
// Supakorn Panyadee 6581117
//

#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main(void)
{
    char block[8192];
    int in, out, nread;
    int length = 0;
    char null = '\0';

    in = open("file.in", O_RDONLY);
    out = open("file.out", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);

    while ((nread = read(in, block, sizeof(block))) > 0)
    {
        write(out, block, nread);
        length += nread;
    }

    int middle = ((length/2)-8);
    lseek(out,middle, SEEK_SET);

    for(int i = 0; i<16; i++) {
        write( out, &null, 1);

    }

    return 0;
}
