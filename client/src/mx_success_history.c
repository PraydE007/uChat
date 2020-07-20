#include "client.h"

static const char *json_to_str(json_object *jobj, char *key) {
    const char *value = NULL;

    value = json_object_get_string(json_object_object_get(jobj, key));
    return value;
}

static t_buf_history init_buf_history() {
    t_buf_history buf_history;

    buf_history.array = NULL;
    buf_history.size_messages = 0;
    buf_history.get_message = NULL;
    buf_history.get_owner = NULL;
    return buf_history;
}

gboolean mx_success_history(void *data) {
    t_s_glade *gui = (t_s_glade *)data;
    t_buf_history buf_history = init_buf_history();
    json_object *jobj = json_tokener_parse(gui->recv_data);

    buf_history.array = json_to_str(jobj, "Array");
    json_object *j_arr = json_tokener_parse(buf_history.array);
    buf_history.size_messages = json_object_array_length(j_arr);
    for (int i = 0; i < buf_history.size_messages; i++) {
        json_object *arr_idx = json_object_array_get_idx(j_arr, i);
            buf_history.get_message = (char *)json_to_str(arr_idx, "Message");
        if (!buf_history.get_message) {
            buf_history.get_message = (char *)json_to_str(arr_idx, "Own_message");
            buf_history.get_owner = (char *)json_to_str(arr_idx, "Login");
            mx_p_own(gui->l_messages,
            buf_history.get_message, buf_history.get_owner);
        }
        else
            mx_p_owned(gui->l_messages, buf_history.get_message, gui->send_to);
    }
    return 0;
}
