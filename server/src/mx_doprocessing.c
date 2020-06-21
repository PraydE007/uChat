#include "server.h"
static void if_disconnect(int socket) {
    printf("\n%s", "User ");
    printf("\033[0;35m");
    printf("%d", socket);
    printf("\033[0m");
    printf("\033[0;31m");
    printf("%s", " Disconnected\n");
    printf("\033[0m");
    close(socket);
}

void *mx_doprocessing (void *data) {
    t_sockbd sockbd = *(t_sockbd *)data;
    int n;
    char buffer[2048];
    json_object *jobj = json_object_new_object();
    json_object *j_result = json_object_new_object();

    while (true) {
        bzero(buffer,2048);
        n = recv(sockbd.sockfd, buffer, sizeof(buffer), 0);
        if (n <= 0) {
            if_disconnect(sockbd.sockfd);
            return 0;
        }
        printf("%s", "\033[0mTaked \033[0m");
        printf("\033[0;36m");
        printf("%s", buffer);
        printf("\033[0m from socket: ");
        printf("\033[1;35m");
        printf("%d", sockbd.sockfd);
        printf("\033[0m");
        printf("%c", '\n');
        jobj = json_tokener_parse(buffer);
        j_result = mx_dbase_handler(jobj, sockbd.bd); //
         printf("json_object_to_json_string(j_result): %s\n", json_object_to_json_string(j_result));
        if (!mx_strcmp(mx_json_to_str(j_result, "Answer"), MX_LOG))
            n = send(sockbd.sockfd, MX_LOG_MES, mx_strlen(MX_LOG_MES), 0);
        else if (!mx_strcmp(mx_json_to_str(j_result, "Answer"), MX_REG))
            n = send(sockbd.sockfd, MX_REG_MES, mx_strlen(MX_REG_MES), 0);
        else if (!mx_strcmp(mx_json_to_str(j_result, "Answer"), MX_ERRLOG))
            n = send(sockbd.sockfd, MX_ERR_LOG, mx_strlen(MX_ERR_LOG), 0);
        else if (!mx_strcmp(mx_json_to_str(j_result, "Answer"), MX_ERRREG))
            n = send(sockbd.sockfd, MX_ERR_REG, mx_strlen(MX_ERR_REG), 0);
        if (n <= 0)
            break;
    }
    //sqlite3_close(db);
    return 0;
}
