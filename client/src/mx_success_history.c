#include "client.h"

static const char *json_to_str(json_object *jobj, char *key) {
    const char *value = NULL;

    value = json_object_get_string(json_object_object_get(jobj, key));
    return value;
}

gboolean mx_success_history(void *data) {
    t_s_glade *gui = (t_s_glade *)data;
    json_object *jobj = json_tokener_parse(gui->recv_data);
    const char *array = json_to_str(jobj, "Array");
    json_object *j_arr = json_tokener_parse(array);
    int size_messages = json_object_array_length(j_arr);
    char *get_message = NULL;
    char *get_owner = NULL;
    for (int i = 0; i < size_messages; i++) {
        json_object *arr_idx = json_object_array_get_idx(j_arr, i);
            get_message = (char *)json_to_str(arr_idx, "Message");
        if (!get_message) {
            get_message = (char *)json_to_str(arr_idx, "Own_message");
            get_owner = (char *)json_to_str(arr_idx, "Login");
            mx_p_own(gui->l_messages, get_message, get_owner);
        }
        else
            mx_p_owned(gui->l_messages, get_message, gui->send_to);
    }
    return 0;
}
