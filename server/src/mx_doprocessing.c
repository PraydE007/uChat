#include "server.h"

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

static t_buf_do_proc init_json () {
    t_buf_do_proc buf_do_proc;

    buf_do_proc.jobj = NULL;
    buf_do_proc.j_result = NULL;
    buf_do_proc.j_socket = NULL;
    return buf_do_proc;
}

void *mx_doprocessing (void *data) {
    t_sockbd sockbd = *(t_sockbd *)data;
    char buffer[MX_MAX_BYTES];
    const char *answer = NULL;
    t_buf_do_proc buf_do_proc = init_json();

    while (true) {
        buf_do_proc.j_result = json_object_new_object();
        bzero(buffer, MX_MAX_BYTES);
        sockbd.n = recv(sockbd.sockfd, buffer, MX_MAX_BYTES, 0);
        buf_do_proc.j_socket = json_object_new_int(sockbd.sockfd);
        if (!error_one(sockbd, sockbd.n))
            break;
        if (mx_is_json(&buf_do_proc.jobj, buffer))
            buf_do_proc = mx_handle_one(buf_do_proc, sockbd);
        else
            mx_add_str_to_js(buf_do_proc.j_result, "Answer", MX_CHEAT_MESSAGE);
        json_object_put(buf_do_proc.jobj);
        answer = json_object_to_json_string(buf_do_proc.j_result);
        sockbd.n = send(sockbd.sockfd, answer, mx_strlen(answer),  0);
        json_object_put(buf_do_proc.j_result);
        if (!error_two(sockbd, sockbd.n))
            break;
    }
    return 0;
}
