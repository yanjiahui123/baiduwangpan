#include <func.h>

int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,2);
    int ret;
    struct in_addr addr;
    ret=inet_aton(argv[1],&addr);
    printf("%x\n",addr.s_addr);
    printf("ip=%s\n",inet_ntoa(addr));
    return 0;
}

