#include <func.h>

int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,2);
    struct hostent *p;
    p=gethostbyname(argv[1]);
    printf("h_name=%s\n",p->h_name);
    int i;
    for(i=0;p->h_aliases[i]!=NULL;i++)
    {
        printf("%s\n",p->h_aliases[i]);
    }
    printf("addrtype=%d\n",p->h_addrtype);
    printf("length=%d\n",p->h_length);
    char ip[16]={0};
    for(i=0;p->h_addr_list[i]!=NULL;i++)
    {
        bzero(&ip,sizeof(ip));
        printf("%s\n",inet_ntop(p->h_addrtype,p->h_addr_list[i],ip,sizeof(ip)));
    }
    return 0;
}

