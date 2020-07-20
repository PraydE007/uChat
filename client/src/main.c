#include "client.h"

static void errors(int sockfd) {
    if (sockfd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }
}

int main(int argc, char **argv) {
    int sockfd;
    int portno;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    int rc = 0;
    //char *send_data = NULL;

    if (argc < 3) {
        fprintf(stderr,"usage %s hostname port\n", argv[0]);
        return 0;
    }
    portno = atoi(argv[2]);
    /* Create a socket point */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (char *)&rc, sizeof(int));
    errors(sockfd);
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr_list[0], (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);
    /* Now connect to the server */
    if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR connecting");
        return 1;
    }
    /////////// Затычка для картинок
//    mx_send_image("/Users/ozahirnyi/uchat/meme_avatar.png", sockfd);
    mx_interface(&argc, &argv, sockfd);

// while(true) {
//    printf("%s", ": ");
//    bzero(buffer,2048);
//    fgets(buffer,2048,stdin);
    // json_object *jobj = json_object_new_object();
    // json_object *j_type = json_object_new_string("Logging");
    // json_object *j_login = json_object_new_string("Vasya");
    // json_object *j_passwd = json_object_new_string(mx_hash("uksgdfj12bf"));
    // json_object_object_add(jobj,"Type", j_type);

//    json_object_object_add(jobj,"Login", j_login);
//    json_object_object_add(jobj,"Passwd", j_passwd);

//    // const char *test;
//    // struct json_object *parsed;
//    // struct json_object *name;
//    /* Send message to the server */
//    send_data = (char *)json_object_to_json_string(jobj);
//    printf("%s\n", send_data);
//    n = send(sockfd, send_data, strlen(send_data), 0);

//    if (n < 0) {
//       perror("ERROR writing to socket");
//       exit(1);
//    }
//    /* Now read server response */
//    bzero(buffer, 2048);
//    n = recv(sockfd, buffer, 2048, 0);

//    if (n <= 0) {
//       printf("%s","Lost connection with the server\n");
//       while (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
//          printf("%s", "Reconnecting...\n");
//          close(sockfd);
//          sockfd = socket(AF_INET, SOCK_STREAM, 0);
//          sleep(3);
//       }
//    }
//    printf("%s", buffer);
// }
//    system("leaks -q uchat");
    return 0;
}
