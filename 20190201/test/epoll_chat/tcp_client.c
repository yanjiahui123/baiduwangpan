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

    int ret=connect(sockfd,(struct sockaddr*)&ser,sizeof(struct sockaddr));
    ERROR_CHECK(ret,-1,"bind");
    fd_set rdset;
    char buf[128]={0};
    while(1)
    {
        FD_ZERO(&rdset);
        FD_SET(STDIN_FILENO,&rdset);
        FD_SET(sockfd,&rdset);
        ret=select(sockfd+1,&rdset,NULL,NULL,NULL);
        if(ret>0)
        {
            if(FD_ISSET(STDIN_FILENO,&rdset))
            {
                bzero(&buf,sizeof(buf));
                ret=read(STDIN_FILENO,buf,sizeof(buf));
                if(0==ret)
                {
                    printf("i will close\n");
                    break;
                }
                send(sockfd,buf,strlen(buf)-1,0);
            }
            if(FD_ISSET(sockfd,&rdset))
            {
                bzero(&buf,sizeof(buf));
                ret=recv(sockfd,buf,sizeof(buf),0);
                if(0==ret)
                {
                    printf("server close\n");
                    break;
                }
                printf("%s\n",buf);
            }
        }
    }
    close(sockfd);
    return 0;
}

