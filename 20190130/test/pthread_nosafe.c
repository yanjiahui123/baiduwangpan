#include <func.h>

void *threadfunc(void *p)
{
    time_t t=time(NULL);
    char *ptime=ctime(&t);
    printf("child %s\n",ptime);
    sleep(5);
    printf("child %s\n",ptime);
}
int main(int argc,char *argv[])
{
    pthread_t thid;
    pthread_create(&thid,NULL,threadfunc,NULL);
    sleep(5);
    time_t t=time(NULL);
    char *mtime=ctime(&t);
    printf("main %s\n",mtime);
    pthread_join(thid,NULL);
    
    return 0;
}

