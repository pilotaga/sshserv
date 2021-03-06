#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <string.h>
#include <unistd.h>
#include <string.h>


char buf[5000];
char message[50];

int main(int argc, char** argv)
{
    
    int sock;
    struct sockaddr_in addr;

    addr.sin_family = AF_INET;
    addr.sin_port = htons(2525);
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    if (inet_addr("den", &addr.sin_addr.s_addr) == 0) 
    {
        puts("IP addres error");
	return 1;	
    }
    scanf("%s", message);    
    while (message[0]!='q')
    {
        sock = socket(AF_INET, SOCK_STREAM, 0);
        if(sock < 0)
        {
            perror("socket");
            exit(1);
        }

        if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
        {
            perror("connect");
            exit(2);
        }

        send(sock, message, 1024, 0);
        recv(sock, buf, 1024, 0);
    
        printf("%s", buf);
        close(sock); 
        scanf("%s", message);
    } 

    return 0;
}
