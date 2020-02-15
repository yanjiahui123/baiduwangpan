#include <func.h>
typedef struct{
    pid_t pid;
    int fds;
    short busy;
}processdata;

void makechild(processdata* ,int );
void childhandle(int );
int tcp_init(int *,char *,char *);
int send_fd(int,int);
int recv_fd(int ,int *);
