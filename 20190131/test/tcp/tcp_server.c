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
    bzero(&client,sizeof(client));
    socklen_t addrlen=sizeof(client);
    new_fd=accept(sockfd,(struct sockaddr*)&client,&addrlen);
    ERROR_CHECK(new_fd,-1,"accept");
    
    char buf[128]={0};
    ret=recv(new_fd,buf,sizeof(buf),0);
    ERROR_CHECK(ret,-1,"recv");
    printf("i am server,gets %s\n",buf);
    send(new_fd,"world",5,0);
    close(new_fd);
    close(sockfd);
    return 0;
}

