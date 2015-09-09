#include <stdio.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <assert.h>
#include <string.h>
#include <strings.h>
#define XIAJUAN "xiajuan"
// ser
int main(int argc, char *argv[])
{
    struct sockaddr_in addr, cliAddr;
    int iCli, iSer;
    char acHost[20] = {0};
    unsigned short usPort;
    char acMsg[512] = {0};
    char *pMsg = NULL;
    int sin_size = sizeof(struct sockaddr_in);
    
    if (3 > argc)
    {
        printf("args err\r\n");
        return -1;
    }
    
    strncpy(acHost, argv[1], 19);
    usPort = (unsigned short)atoi(argv[2]);
    printf("Host:%s:%d\r\n", acHost, usPort);
    iSer = socket(AF_INET, SOCK_STREAM, 0);
    assert(0 < iSer);
    addr.sin_family = AF_INET;
    addr.sin_port   = htons(usPort);
    addr.sin_addr.s_addr = inet_addr(acHost);
    bzero(&addr.sin_zero, 0);
    if (0 > bind(iSer, (struct sockaddr*)&addr, sizeof(struct sockaddr)))
    {
        perror("bind err");
        return -1;
    }
    
    if (0 > listen(iSer, 1))
    {
        perror("listen");
        return -1;
    }
    
    iCli = accept(iSer, (struct sockaddr*)&cliAddr, &sin_size);
    assert(0 < iCli);
    pMsg = acMsg;
    
    while (1)
    {
        recv(iCli, pMsg, 511, 0);
        printf("%s\r\n", pMsg);
    }
     
    close(iCli);
    close(iSer);
    
    return 0;
}
