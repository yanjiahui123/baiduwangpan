#include <func.h>

int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,3);

    int sockfd=socket(AF_INET,SOCK_DGRAM,0);
    ERROR_CHECK(sockfd,-1,"socket");
    printf("sockfd=%d\n",sockfd);

    struct sockaddr_in ser;
    bzero(&ser,sizeof(ser));
    ser.sin_family=AF_INET;
    ser.sin_port=htons(atoi(argv[2]));
    ser.sin_addr.s_addr=inet_addr(argv[1]);
    
    char buf[128]={0};
    socklen_t addrlen=sizeof(struct sockaddr);
    fd_set rdset;
    sendto(sockfd,"1",1,0,(struct sockaddr*)&ser,addrlen);
    int ret;
    while(1)
    {
        FD_ZERO(&rdset);
        FD_SET(STDIN_FILENO,&rdset);
        FD_SET(sockfd,&rdset);
        ret=select(sockfd+1,&rdset,NULL,NULL,NULL);
        if(ret>0){
            if(FD_ISSET(STDIN_FILENO,&rdset))
            {
                bzero(&buf,sizeof(buf));
                ret=read(STDIN_FILENO,buf,sizeof(buf));
                ERROR_CHECK(ret,-1,"read");
                sendto(sockfd,buf,strlen(buf)-1,0,(struct sockaddr*)&ser,addrlen);
            }
            if(FD_ISSET(sockfd,&rdset))
            {
                bzero(&buf,sizeof(buf));
                ret=recvfrom(sockfd,buf,sizeof(buf),0,(struct sockaddr*)&ser,&addrlen);
                ERROR_CHECK(ret,-1,"recvfrom");
                printf("%s\n",buf);
            }
        }
    }
    close(sockfd);
    return 0;
}
