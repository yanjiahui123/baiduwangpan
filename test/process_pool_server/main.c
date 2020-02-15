#include "process_pool.h"

int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,4);// ip port processNUm
    int processNum=atoi(argv[3]);
    processdata * pManage=( processdata *)calloc(processNum,sizeof(processdata));
    makechild(pManage,processNum);//create child process
    int sockfd;
    tcp_init(&sockfd,argv[1],argv[2]);
    
    int epfd=epoll_create(1);
    struct epoll_event event,*evs;
    evs=(struct epoll_event*)calloc(processNum+1,sizeof(struct epoll_event));
    event.events=EPOLLIN;
    event.data.fd=sockfd;
    epoll_ctl(epfd,EPOLL_CTL_ADD,sockfd,&event);
    
    int readyNum,i,new_fd,j;
    char flag=1;
    for(i=0;i<processNum;i++)
    {
        event.data.fd=pManage[i].fds;
        epoll_ctl(epfd,EPOLL_CTL_ADD,pManage[i].fds,&event);
    }
    while(1)
    {
        readyNum=epoll_wait(epfd,evs,processNum+1,-1);
        for(i=0;i<readyNum;i++)
        {
            if(sockfd==evs[i].data.fd)
            {
                new_fd=accept(sockfd,NULL,NULL);
                for(j=0;j<processNum;j++)
                {
                    if(0==pManage[j].busy)
                    {
                        send_fd(pManage[j].fds,new_fd);
                        close(new_fd);
                        pManage[j].busy=1;
                        printf("%d is busy\n",pManage[j].pid);
                        break;
                    }
                }
            }
            for(j=0;j<processNum;j++)
            { 
                if(pManage[j].fds==evs[j].data.fd)
                {
                    read(pManage[j].fds,&flag,sizeof(char));
                    pManage[j].busy=0;
                    printf("%d is not busy\n",pManage[j].pid);
                    break;
                }              

            }
        }
    }
    return 0;
}

