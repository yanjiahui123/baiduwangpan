#include <func.h>

int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,3);

    int sockfd=socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(sockfd,-1,"socket");
    printf("sockfd=%d\n",sockfd);

    struct sockaddr_in ser;
    bzero(&ser,sizeof(ser));
    ser.sin_family=AF_INET;
    ser.sin_port=htons(atoi(argv[2]));
    ser.sin_addr.s_addr=inet_addr(argv[1]);

    int ret=bind(sockfd,(struct sockaddr*)&ser,sizeof(struct sockaddr));
    ERROR_CHECK(ret,-1,"bind");
    listen(sockfd,10);

    int new_fd;
    struct sockaddr_in client;
    socklen_t addrlen=sizeof(client);

    char buf[128]={0};
    fd_set rdset,recordset;
    FD_SET(STDIN_FILENO,&recordset);
    FD_SET(sockfd,&recordset);
    while(1)
    {
        FD_ZERO(&rdset);
        memcpy(&rdset,&recordset,sizeof(fd_set));
        ret=select(13,&rdset,NULL,NULL,NULL);
        if(ret>0)
        {
            printf("123\n");
            if(FD_ISSET(sockfd,&rdset))
            {
                bzero(&client,sizeof(client));
                printf("test\n");
                new_fd=accept(sockfd,(struct sockaddr*)&client,&addrlen);
                ERROR_CHECK(new_fd,-1,"accept");
                printf("client ip=%s,port=%d\n",inet_ntoa(client.sin_addr),ntohs(client.sin_port));
                FD_SET(new_fd,&recordset);
            }
            if(FD_ISSET(STDIN_FILENO,&rdset))
            {
                bzero(&buf,sizeof(buf));
                ret=read(STDIN_FILENO,buf,sizeof(buf)-1);
                if(0==ret)
                {
                    printf("i will close\n");
                    break;
                }
                send(new_fd,buf,strlen(buf)-1,0);
            }
            if(FD_ISSET(new_fd,&rdset))
            {
                bzero(&buf,sizeof(buf));
                ret=recv(new_fd,buf,sizeof(buf)-1,0);
                if(0==ret)
                {
                    printf("client close\n");
                    FD_CLR(new_fd,&recordset);
                    close(new_fd);
                }
                printf("%s\n",buf);
            }

        }
    }
    close(new_fd);
    close(sockfd);
    return 0;
}

