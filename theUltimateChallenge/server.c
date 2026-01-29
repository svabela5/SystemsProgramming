#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>

#define PORT 11111
char* out_file;
pthread_mutex_t file_mutex;

void* handleConnection(void* ptr){
    int connfd = *((int*) ptr);
    free(ptr);
    char buf[128];
    while(1){
        int n = recv(connfd, buf, sizeof(buf) - 1, 0);
        if(n>0){
        buf[n] = '\0';
            printf("Server received: %s\n", buf);
            pthread_mutex_lock(&file_mutex);
            FILE* fp = fopen(out_file, "a");

            if (fp)
            {
                fprintf(fp, "%s\n", buf);
                printf("Data Logged: %s", buf);
                fclose(fp);
            }
            pthread_mutex_unlock(&file_mutex);
            send(connfd, "Data Logged successfully\n", 25, 0);
        } else {
            printf("Error, Closing Connection \n");
            break;
        }
    }
    printf("Closing Connection\n");
    close(connfd);
}

int main(int argc, char* argv[]) {
    if (argc < 2)
    {
        printf("Output file must be specified \n");
        return(0);
    }

    out_file = argv[1];
    pthread_mutex_init(&file_mutex, NULL);

    int listenfd, connfd;
    struct sockaddr_in srv_addr = {0};
    char buf[128];

    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    srv_addr.sin_family = AF_INET;
    srv_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    srv_addr.sin_port = htons(PORT);

    bind(listenfd, (struct sockaddr *)&srv_addr, sizeof(srv_addr));
    listen(listenfd, 5);

    printf("Server listening on port %d...\n", PORT);

    while(1){
        connfd = accept(listenfd, NULL, NULL);
        int* connfdPtr = (int*) malloc(sizeof(int));
        *connfdPtr = connfd;
        pthread_t thread;

        pthread_create(&thread, NULL, handleConnection, connfdPtr);
        pthread_detach(thread);
    }
    pthread_mutex_destroy(&file_mutex);
	printf("Press any key to exit...");// pause before closing
    getchar();
    close(listenfd);
    printf("Server exiting...\n");
    return 0;
}
