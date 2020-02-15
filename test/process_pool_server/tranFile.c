#include "process_pool.h"

int tranfile(int new_fd)
{
    train t;
    bzero(&t,sizeof(t));
    strcpy(t.buf,DOWNLOAD);
    t.datalen=strlen(DOWNLOAD);
    
    //send file name
    send(new_fd,&t,4+t.datalen,0);
    //send file contain
    int fd=open(DOWNLOAD,O_RDONLY);
    while(t.datalen=read(fd,t.buf,sizeof(t.buf)))
    {
        printf("11\n");
        send(new_fd,&t,4+t.datalen,0);
    }
    //send file over
    send(new_fd,&t,4+t.datalen,0);
    close(new_fd);
    return 0;
}

