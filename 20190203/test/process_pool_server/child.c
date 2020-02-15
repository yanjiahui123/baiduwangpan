#include "process_pool.h"

void makechild(processdata *pManage,int processNum)
{
    int i;
    pid_t pid;
    int fds[2];
    for(i=0;i<processNum;i++)
    {
        socketpair(AF_LOCAL,SOCK_STREAM,0,fds);
        pid=fork();
        if(!pid)
        {
            close(fds[1]);
            childhandle(fds[0]);    
        }
        close(fds[0]);
        pManage[i].pid=pid;
        pManage[i].fds=fds[1];
    }
}

void childhandle(int fds)
{
    int new_fd;
    char flag=1;
    while(1)
    {
        recv_fd(fds,&new_fd);
        printf("i am child,get task\n");
        tranfile(new_fd);//child process send file
        close(new_fd);
        write(fds,&flag,sizeof(char));
    }
}
