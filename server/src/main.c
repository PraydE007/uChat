#include "server.h"
#include <stdio.h>
#include <string.h>

static void accepting(t_sockbd *sockbd) {
    if (sockbd->sockfd < 0) {
        write(sockbd->log_sescr, "ERROR on accept\n", 16);
        exit(1);
    }
    else {
        write(sockbd->log_sescr, "User connected from socket ", 27);
        write(sockbd->log_sescr, mx_itoa(sockbd->sockfd), 1);
        write(sockbd->log_sescr, "\n", 1);
    }
}

static void usage_socket(int sockfd, t_sockbd *sockbd) {
    sockbd->bd = NULL;
    sockbd->n = 0;
    sockbd->sockfd = 0;
    sockbd->login = NULL;
    sockbd->log_sescr = mx_create_log();
    if (sockfd < 0) {
        write(sockbd->log_sescr, "ERROR: opening socket\n", 22);
        exit(1);
    }
}

static struct sockaddr_in init_server_address(int sockfd, int portno, int rc) {
    struct sockaddr_in serv_addr;

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (char *)&rc, sizeof(int));
    return serv_addr;
}

static void usage_port(int argc, char **argv, struct sockaddr_in *serv_addr,
                       t_sockbd *sockbd) {
    int portno;
    int rc = 1;

    if (argc < 2) {
        fprintf(stderr,"usage: %s port\n", argv[0]);
        exit(1);
    }
    mx_demonize();
    sockbd->log_sescr = mx_create_log();
    sockbd->sockfd2 = socket(AF_INET, SOCK_STREAM, 0);
    usage_socket(sockbd->sockfd2, sockbd);
    portno = atoi(argv[1]);
    *serv_addr = init_server_address(sockbd->sockfd2, portno, rc);
}

int main(int argc, char **argv) {
    int clilen;
    struct sockaddr_in serv_addr, cli_addr;
    pthread_t x = 0;
    t_sockbd *sockbd = (t_sockbd *)malloc(sizeof(t_sockbd));

    usage_port(argc, argv, &serv_addr, sockbd);
    if (bind(sockbd->sockfd2, (struct sockaddr *) &serv_addr,
        sizeof(serv_addr)) < 0) {
        write(sockbd->log_sescr, "ERROR on binding\n", 17);
        exit(1);
    }
    listen(sockbd->sockfd2, 5);
    clilen = sizeof(cli_addr);
    mx_data_base_creation(&sockbd->bd);
    while (true) {
        sockbd->sockfd = accept(sockbd->sockfd2, (struct sockaddr *)&cli_addr,
                               (socklen_t *)&clilen);
        accepting(sockbd);
        pthread_create(&x, NULL, mx_doprocessing, (void *)sockbd);
    }
    sqlite3_close(sockbd->bd);
}
