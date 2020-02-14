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

    
    send(sockfd,"hello",5,0);
    char buf[128]={0};
    ret=recv(sockfd,buf,sizeof(buf),0);
    ERROR_CHECK(ret,-1,"recv");
    printf("i am client,get %s\n",buf);
    close(sockfd);
    return 0;
}

