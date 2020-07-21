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
    int n = 0;
    char buffer[MX_MAX_BYTES];
    const char *answer = NULL;
    json_object *jobj = NULL;
    json_object *j_result = NULL;
    json_object *j_socket = NULL;

    while (true) {
        j_result = json_object_new_object();
        bzero(buffer, MX_MAX_BYTES);
        n = recv(sockbd.sockfd, buffer, MX_MAX_BYTES, 0);
        j_socket = json_object_new_int(sockbd.sockfd);
        if (n <= 0) {
            if_disconnect(sockbd);
            mx_user_deactivate(sockbd.bd, sockbd.sockfd);
            break;
        }
        if (mx_is_json(&jobj, buffer)) {
            json_object_object_add(jobj,"Socket", j_socket);
            log_add_info(sockbd, jobj);
            j_result = mx_dbase_handler(jobj, sockbd.bd);
        }
        else
            mx_add_str_to_js(j_result, "Answer", MX_CHEAT_MESSAGE);
        answer = json_object_to_json_string(j_result);
        n = send(sockbd.sockfd, answer, mx_strlen(answer),  0);
        json_object_put(jobj);
        json_object_put(j_result);
        if (n <= 0) {
            mx_user_deactivate(sockbd.bd, sockbd.sockfd);
            break;
        }
    }
    return 0;
}
