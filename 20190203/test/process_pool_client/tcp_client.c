#include <func.h>

int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,3);
    struct sockaddr_in ser;
    bzero(&ser,sizeof(ser));
    ser.sin_family=AF_INET;
    ser.sin_port=htons(atoi(argv[2]));
    ser.sin_addr.s_addr=inet_addr(argv[1]);
    int sockfd=socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(sockfd,-1,"socket");
    
    int ret=connect(sockfd,(struct sockaddr*)&ser,sizeof(struct sockaddr));
    ERROR_CHECK(ret,-1,"connect");

    int datalen=0;
    char buf[1000]={0};
    recv(sockfd,&datalen,sizeof(int),0);
    recv(sockfd,buf,datalen,0);
    int fd=open(buf,O_WRONLY|O_CREAT,0666);
    ERROR_CHECK(fd,-1,"open");
    while(1)
    {
        recv(sockfd,&datalen,sizeof(int),0);
        if(datalen>0)
        {
            printf("22\n");
            bzero(&buf,sizeof(buf));
            recv(sockfd,buf,datalen,0);
            write(fd,buf,datalen);
        }
        else
        {
            close(fd);
            printf("recv success\n");
            break;
        }
    }
    close(sockfd);
    return 0;
}

