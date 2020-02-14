#include <func.h>

int main(int argc,char *argv[])
{
    unsigned short port=0x1234,nport;
    nport=htons(port);
    printf("%p\n",nport);
    return 0;
}

