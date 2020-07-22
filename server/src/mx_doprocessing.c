#include "server.h"

static void log_add_info(t_sockbd sockbd, json_object *jobj) {
    write (sockbd.log_sescr, "Taked ", 6);
    write (sockbd.log_sescr, json_object_to_json_string(jobj),
           strlen(json_object_to_json_string(jobj)));
    write (sockbd.log_sescr, " from socket: ", 14);
    write (sockbd.log_sescr, mx_itoa(sockbd.sockfd), 1);
    write (sockbd.log_sescr, "\n", 1);
}

static bool error_one(t_sockbd sockbd, int n) {
    if (n <= 0) {
        write (sockbd.log_sescr, "User ", 5);
        write (sockbd.log_sescr, mx_itoa(sockbd.sockfd), 1);
        write (sockbd.log_sescr, " Disconnected\n", 14);
        close(sockbd.sockfd);
        mx_user_deactivate(sockbd.bd, sockbd.sockfd);
        return false;
    }
    return true;
}

static bool error_two(t_sockbd sockbd, int n) {
    if (n <= 0) {
        mx_user_deactivate(sockbd.bd, sockbd.sockfd);
        return false;
    }
    return true;
}

// static void doprocessing_cycle(json_object *j_result, json_object *j_socket,
//                                 t_sockbd sockbd, char *buffer) {
//     // t_sockbd sockbd = *(t_sockbd *)data;
//     // int n = 0;
//     // char buffer[MX_MAX_BYTES];
//     // const char *answer = NULL;
//     json_object *jobj = NULL;
//     // json_object *j_result = NULL;
//     // json_object *j_socket = NULL;

//     if (mx_is_json(&jobj, buffer)) {
//         json_object_object_add(jobj,"Socket", j_socket);
//         log_add_info(sockbd, jobj);
//         j_result = mx_dbase_handler(jobj, sockbd.bd);
//     }
//     else
//         mx_add_str_to_js(j_result, "Answer", MX_CHEAT_MESSAGE);
//     json_object_put(jobj);
// }

void *mx_doprocessing (void *data) {
    t_sockbd sockbd = *(t_sockbd *)data;
    char buffer[MX_MAX_BYTES];
    const char *answer = NULL;
    json_object *jobj = NULL;
    json_object *j_result = NULL;
    json_object *j_socket = NULL;

    while (true) {
        j_result = json_object_new_object();
        bzero(buffer, MX_MAX_BYTES);
        sockbd.n = recv(sockbd.sockfd, buffer, MX_MAX_BYTES, 0);
        j_socket = json_object_new_int(sockbd.sockfd);
        if (!error_one(sockbd, sockbd.n))
            break;
        // doprocessing_cycle(j_result, j_socket, sockbd, buffer);
        if (mx_is_json(&jobj, buffer)) {
            json_object_object_add(jobj,"Socket", j_socket);
            log_add_info(sockbd, jobj);
            j_result = mx_dbase_handler(jobj, sockbd.bd);
        }
        else
            mx_add_str_to_js(j_result, "Answer", MX_CHEAT_MESSAGE);
        json_object_put(jobj);
        answer = json_object_to_json_string(j_result);
        sockbd.n = send(sockbd.sockfd, answer, mx_strlen(answer),  0);
        json_object_put(j_result);
        if (!error_two(sockbd, sockbd.n))
            break;
    }
    return 0;
}
