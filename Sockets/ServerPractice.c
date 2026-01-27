#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define PORT 8080

int main() {
    int listenfd, connfd;
    struct sockaddr_in srv_addr = {0};
    char buffer[128];

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd == -1) {
        printf("socket() failed\n");
        return -1;
    }

    srv_addr.sin_family = AF_INET;
    srv_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    srv_addr.sin_port = htons(PORT);

    int check = bind(listenfd, (struct sockaddr *)&srv_addr, sizeof(srv_addr));
    if (check != 0) {
        printf("bind() failed\n");
        close(listenfd);
        return -2;
    }
    check = listen(listenfd, 5);
    if(check!= 0) {
        printf("listen() failed\n");
        close(listenfd);
        return -3;
    }
    printf("Server listening on port %d...\n", PORT);
    
    connfd = accept(listenfd, NULL, NULL); //ignore client address
    while (1)
    {
        if (connfd == -1) {
            printf("accept() failed\n");
            //on real servers we do not disconnect but aretry 
            
        } else { 
            int n = recv(connfd, buffer, sizeof(buffer)-1, 0);
            if(n>0){
                int bytes;
                printf("Server received: %s", buffer);
                if (strncmp(buffer, "ping", 4) == 0)
                {
                    bytes = send(connfd, "Pong\n", 5, 0);
                }else if (strncmp(buffer, "time", 4) == 0){
                    bytes = send(connfd, "It's Almost noon\n", 17, 0);
                } else if (strncmp(buffer, "quit", 4) == 0)
                {
                    bytes = send(connfd, "Server Says Goodbye\n", 20, 0);
                }else{
                    bytes = send(connfd, "Unknown Command :(\n", 19, 0);
                }

                if (bytes == -1) {
                    printf("send() failed\n");
                }
                if (strncmp(buffer, "quit", 4) == 0)
                {
                    break;
                }

                

            } else {
                printf("Connection Error closing connection");
                break;
            }
        }
    }
}