#include "client.h"

static void errors(int sockfd) {
    if (sockfd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }
}

static void second_errors(int argc, char **argv) {
    if (argc < 3) {
        fprintf(stderr,"usage %s hostname port\n", argv[0]);
        exit(1);
    }
}

static void err_fo_server() {
    fprintf(stderr,"ERROR, no such host\n");
    exit(1);
}

int main(int argc, char **argv) {
    int sockfd;
    int portno;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    int rc = 0;

    second_errors(argc, argv);
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (char *)&rc, sizeof(int));
    errors(sockfd);
    server = gethostbyname(argv[1]);
    if (server == NULL)
        err_fo_server();
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr_list[0],
    (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR connecting");
        return 1;
    };
    mx_interface(&argc, &argv, sockfd);
    return 0;
}
