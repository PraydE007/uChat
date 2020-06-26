#include "server.h"
static void if_disconnect(t_sockbd sockbd) {
    write (sockbd.log_sescr, "User ", 5);
    write (sockbd.log_sescr, mx_itoa(sockbd.sockfd), 1);
    write (sockbd.log_sescr, " Disconnected\n", 14);
    close(sockbd.sockfd);
}

static void log_add_info(t_sockbd sockbd, json_object *jobj) {
    write (sockbd.log_sescr, "Taked ", 6);
    write (sockbd.log_sescr, json_object_to_json_string(jobj),
        strlen(json_object_to_json_string(jobj)));
    write (sockbd.log_sescr, " from socket: ", 14);
    write (sockbd.log_sescr, mx_itoa(sockbd.sockfd), 1);
    write (sockbd.log_sescr, "\n", 1);
}

void *mx_doprocessing (void *data) {
    t_sockbd sockbd = *(t_sockbd *)data;
    int n;
    char buffer[2048];
    json_object *jobj = json_object_new_object();
    json_object *j_result = json_object_new_object();
    json_object *j_socket = json_object_new_int(sockbd.sockfd);

    while (true) {
        bzero(buffer,2048);
        n = recv(sockbd.sockfd, buffer, sizeof(buffer), 0);
        //n = send(sockbd.sockfd, buffer, sizeof(buffer), 0);
        if (n <= 0) {
            if_disconnect(sockbd);
            break;
        }
        jobj = json_tokener_parse(buffer);
        json_object_object_add(jobj,"Socket", j_socket);
        log_add_info(sockbd, jobj);
        j_result = mx_dbase_handler(jobj, sockbd.bd); //
        //json_object_put(jobj);
        //printf("json_object_to_json_string(j_result): %s\n", json_object_to_json_string(j_result)); //
        if (!mx_strcmp(mx_json_to_str(j_result, "Answer"), MX_LOG))
            n = send(sockbd.sockfd, MX_LOG_MES, mx_strlen(MX_LOG_MES),  0);
        else if (!mx_strcmp(mx_json_to_str(j_result, "Answer"), MX_REG))
            n = send(sockbd.sockfd, MX_REG_MES, mx_strlen(MX_REG_MES),  0);
        else if (!mx_strcmp(mx_json_to_str(j_result, "Answer"), MX_ERRLOG))
            n = send(sockbd.sockfd, MX_ERR_LOG, mx_strlen(MX_ERR_LOG),  0);
        else if (!mx_strcmp(mx_json_to_str(j_result, "Answer"), MX_ERRREG))
            n = send(sockbd.sockfd, MX_ERR_REG, mx_strlen(MX_ERR_REG),  0);
        if (n <= 0)
            break;
    }
    return 0;
}
