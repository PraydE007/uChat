#include "client.h"

void *mx_client_recv(void *data) {
    int n = 0;
    char buffer[2048];
    int sockfd = *(int *)data;

    while (true) {
        bzero(buffer, 2048);
        n = recv(sockfd, buffer, sizeof(buffer), MSG_WAITALL);
            printf("%s\n", buffer);
        if (n <= 0) {
            printf("%s\n", "SERVER_DOWN!");
            exit(0);
        }
    }
    return NULL;
}
