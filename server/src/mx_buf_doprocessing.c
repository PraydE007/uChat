#include "server.h"

static void log_add_info(t_sockbd sockbd, json_object *jobj) {
    write (sockbd.log_sescr, "Taked ", 6);
    write (sockbd.log_sescr, json_object_to_json_string(jobj),
           strlen(json_object_to_json_string(jobj)));
    write (sockbd.log_sescr, " from socket: ", 14);
    write (sockbd.log_sescr, mx_itoa(sockbd.sockfd), 1);
    write (sockbd.log_sescr, "\n", 1);
}

t_buf_do_proc mx_handle_one(t_buf_do_proc buf_do_proc, t_sockbd sockbd) {
    json_object_object_add(buf_do_proc.jobj,"Socket", buf_do_proc.j_socket);
    log_add_info(sockbd, buf_do_proc.jobj);
    buf_do_proc.j_result = mx_dbase_handler(buf_do_proc.jobj, sockbd.bd);
    return buf_do_proc;
}
