#include <func.h>

void sighander(int signum)
{
    printf("%d is coming\n",signum);
}

int main(int argc,char *argv[])
{
    signal(SIGINT,SIG_DFL);
    while(1);
    return 0;
}

