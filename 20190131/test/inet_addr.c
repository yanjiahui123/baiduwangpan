#include <func.h>

int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,2);
    int ret;
    struct in_addr addr;
    ret=inet_aton(argv[1],&addr);
    printf("%x,%x\n",addr.s_addr,inet_addr(argv[1]));
    return 0;
}

