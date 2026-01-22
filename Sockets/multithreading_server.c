
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void *handle_client(void *arg) {
    int connfd = *(int *)arg;
    free(arg);

    char buffer[BUFFER_SIZE];

    while (1) {
        memset(buffer, 0, BUFFER_SIZE);

        int n = recv(connfd, buffer, BUFFER_SIZE - 1, 0);
        if (n <= 0) {
            break;
        }

        printf("Client says: %s", buffer);

        for (int i = 0; buffer[i]; i++) {
            buffer[i] = toupper((unsigned char)buffer[i]);
        }

        send(connfd, buffer, strlen(buffer), 0);
    }

    close(connfd);
    return NULL;
}

int main() {
    int listenfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    int opt = 1;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(listenfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind");
        close(listenfd);
        exit(EXIT_FAILURE);
    }

    if (listen(listenfd, 10) < 0) {
        perror("listen");
        close(listenfd);
        exit(EXIT_FAILURE);
    }

    printf("Threaded server listening on port %d...\n", PORT);

    while (1) {
        int *connfd = malloc(sizeof(int));
        if (!connfd) {
            perror("malloc");
            continue;
        }

        *connfd = accept(listenfd,
                          (struct sockaddr *)&client_addr,
                          &client_len);

        if (*connfd < 0) {
            perror("accept");
            free(connfd);
            continue;
        }

        pthread_t tid;
        if (pthread_create(&tid, NULL, handle_client, connfd) != 0) {
            perror("pthread_create");
            close(*connfd);
            free(connfd);
            continue;
        }

        pthread_detach(tid);
    }

    close(listenfd);
    return 0;
}
