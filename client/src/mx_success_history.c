#include "client.h"

static const char *json_to_str(json_object *jobj, char *key) {
    const char *value = NULL;

    value = json_object_get_string(json_object_object_get(jobj, key));
    return value;
}

gboolean mx_success_history(void *data) {
    t_s_glade *gui = (t_s_glade *)data;
    json_object *jobj = json_tokener_parse(gui->recv_data);
    int size_messages = json_object_array_length(jobj);
    const char *get_message = NULL;
    // printf("SIZE :%d\n", size_messages);
    for (int i = 1; i < size_messages; i++) {
        json_object *arr_idx = json_object_array_get_idx(jobj, i);
            get_message = json_to_str(arr_idx, "Message");
        if (!get_message) {
            get_message = json_to_str(arr_idx, "Own_message");
            mx_p_own(gui->l_messages, get_message, "Хто овнер блеать?");
        }
        else {
            mx_p_owned(gui->l_messages, get_message, "Хто овнер блеать?");
        }

    }
    return 0;
}
