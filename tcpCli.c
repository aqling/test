#include <stdio.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <assert.h>
#include <string.h>
#include <strings.h>

#define LILING "liling"

// cli
int main(int argc, char *argv[])
{
    struct sockaddr_in addr;
    int iCli;
    char acHost[20] = {0};
    unsigned short usPort;
    char acMsg[512] = {0};
    char *pMsg = NULL;
    
    if (3 > argc)
    {
        printf("args err\r\n");
        return -1;
    }
    
    strncpy(acHost, argv[1], 19);
    usPort = (unsigned short)atoi(argv[2]);
    printf("connect to:%s:%d\r\n", acHost, usPort);

    iCli = socket(AF_INET, SOCK_STREAM, 0);
    assert(0 < iCli);
    addr.sin_family = AF_INET;
    addr.sin_port   = htons(usPort);
    addr.sin_addr.s_addr = inet_addr(acHost);
    bzero(&addr.sin_zero, 0);
    if (0 > connect(iCli, (struct sockaddr*)&addr, sizeof(struct sockaddr_in)))
    {
        perror("connect err");
        return -1;
    }
    
    while (1)
    {
        pMsg = fgets(acMsg, 511, stdin);
        if (0 == strcmp(pMsg, "bye"))
        {
            break;
        }
        
        send(iCli, pMsg, strlen(pMsg), 0);
    }
     
    close(iCli);
    
    return 0;
}
