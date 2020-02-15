#include <func.h>
#define DOWNLOAD "file"
typedef struct{
    pid_t pid;
    int fds;
    short busy;
}processdata;

typedef struct{
    int datalen;
    char buf[1000];
}train;

void makechild(processdata* ,int );
void childhandle(int );
int tcp_init(int *,char *,char *);
int send_fd(int,int);
int recv_fd(int ,int *);
int tranfile(int );
