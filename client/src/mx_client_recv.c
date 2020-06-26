#include "client.h"

void *mx_client_recv(void *data) {
    int n = 0;
    char buffer[2048];
    int sockfd = *(int *)data;

    while (true) {
        bzero(buffer, 2048);
        n = recv(sockfd, buffer, sizeof(buffer), MSG_WAITALL);
            printf("%s\n", buffer);
    }
    return NULL;
}
