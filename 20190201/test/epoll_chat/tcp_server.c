#include <func.h>

int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,3);

    int sockfd=socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(sockfd,-1,"socket");
    printf("sockfd=%d\n",sockfd);

    int reuse=1;
    int ret=setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(int));
    ERROR_CHECK(ret,-1,"setsockopt");

    struct sockaddr_in ser;
    bzero(&ser,sizeof(ser));
    ser.sin_family=AF_INET;
    ser.sin_port=htons(atoi(argv[2]));
    ser.sin_addr.s_addr=inet_addr(argv[1]);

    ret=bind(sockfd,(struct sockaddr*)&ser,sizeof(struct sockaddr));
    ERROR_CHECK(ret,-1,"bind");

    listen(sockfd,10);

    int new_fd;
    struct sockaddr_in client;

    char buf[128]={0};
    int epfd=epoll_create(1);
    struct epoll_event event,evs[3];
    event.events=EPOLLIN;
    event.data.fd=STDIN_FILENO;
    ret=epoll_ctl(epfd,EPOLL_CTL_ADD,STDIN_FILENO,&event);
    ERROR_CHECK(ret,-1,"epoll_ctl");
    event.data.fd=sockfd;
    ret=epoll_ctl(epfd,EPOLL_CTL_ADD,sockfd,&event);
    ERROR_CHECK(ret,-1,"epoll_ctl");
    int i,readyNum;
    while(1)
    {
        readyNum=epoll_wait(epfd,evs,3,-1);

        for(i=0;i<readyNum;i++)
        {
            if(sockfd==evs[i].data.fd)
            {

                bzero(&client,sizeof(client));
                socklen_t addrlen=sizeof(client);
                new_fd=accept(sockfd,(struct sockaddr*)&client,&addrlen);
                ERROR_CHECK(new_fd,-1,"accept");
                printf("client ip=%s,port=%d\n",inet_ntoa(client.sin_addr),ntohs(client.sin_port));
                event.data.fd=new_fd;
                epoll_ctl(epfd,EPOLL_CTL_ADD,new_fd,&event);
            }
            if(STDIN_FILENO==evs[i].data.fd)
            {
                bzero(&buf,sizeof(buf));
                ret=read(STDIN_FILENO,buf,sizeof(buf));
                if(0==ret)
                {
                    printf("i will close\n");
                    goto end;
                }
                send(new_fd,buf,strlen(buf)-1,0);
            }
            if(new_fd==evs[i].data.fd)
            {
                bzero(&buf,sizeof(buf));
                ret=recv(new_fd,buf,sizeof(buf),0);
                if(0==ret)
                {
                    printf("client close\n");
                    epoll_ctl(epfd,EPOLL_CTL_DEL,new_fd,&event);
                    break;
                }
                printf("%s\n",buf);
            }

        }
    }
end:
    close(new_fd);
    close(sockfd);
    return 0;
}

