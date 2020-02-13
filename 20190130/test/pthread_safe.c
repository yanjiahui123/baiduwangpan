#include <func.h>

void *threadfunc(void *p)
{
    time_t t=time(NULL);
    char buf[20]={0}; 
    ctime_r(&t,buf);
    printf("child %s\n",buf);
    sleep(5);
    t=time(NULL);
    ctime_r(&t,buf);
    printf("child %s\n",buf);
}
int main(int argc,char *argv[])
{
    pthread_t thid;
    pthread_create(&thid,NULL,threadfunc,NULL);
    sleep(5);
    time_t t=time(NULL);
    char buf[128]={0};
    ctime_r(&t,buf);
    printf("main %s\n",buf);
    pthread_join(thid,NULL);
    
    return 0;
}

