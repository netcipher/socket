#include "stdio.h"
#include <sys/socket.h> //socket
#include "string.h"
#include "unistd.h" //write /read from socket
#include <arpa/inet.h>

int main(void)
{
    printf("added by Ubuntu\n");
    printf("added by mac\n");
    printf("modified in new branch\n");
    int sock_listen, sock_client, iSize, iLength;
    struct sockaddr_in server_addr, client_addr;
    char recvBuf[200] = {0};
    char recvBufTmp[200] = {0};
    char* pHead = "Server: ";
    int iOption =0;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr  = INADDR_ANY;
    server_addr.sin_port   = htons(9992);
    
    if((sock_listen = socket(AF_INET, SOCK_STREAM, 0))<0)
    {
	printf("create socket failed\n");
	return -1;
    }
    
    setsockopt(sock_listen, SOL_SOCKET, 0, &iOption, sizeof(iOption));

    if((bind(sock_listen, (struct sockaddr*)&server_addr, sizeof(server_addr))) < 0)
    {
	printf("bind failed\n");
	return -1;
    }
    listen(sock_listen, 5);

    if((sock_client = accept(sock_listen, (struct sockaddr*)&client_addr, &iSize))<0)
    {
	printf("accept failed \n");
	return -1;
    }
    //read and write
    while((iLength = recv(sock_client, recvBuf, 200, 0))>0)
    {
	memcpy(recvBufTmp, pHead, strlen(pHead));
        memcpy(recvBufTmp+ strlen(pHead), recvBuf, iLength);
 	write(sock_client, recvBufTmp, strlen(recvBufTmp));
	
	memset(recvBuf, 0, 200);
        memset(recvBufTmp, 0, 200);
    }
    
    close(sock_listen);
    close(sock_client);
    return 0;
}
