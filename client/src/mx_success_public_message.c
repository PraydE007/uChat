#include "client.h"

static const char *json_to_str(json_object *jobj, char *key) {
    const char *value = NULL;

    value = json_object_get_string(json_object_object_get(jobj, key));
    return value;
}

gboolean mx_success_public_message(void *data) {
    t_s_glade *gui = (t_s_glade *)data;
    json_object *jobj = json_tokener_parse(gui->recv_data);
    const char *message = json_to_str(jobj, "Message");
    const char *group = json_to_str(jobj, "Chat_name");
    const char *sender = json_to_str(jobj, "Sender");

    if (gui->send_to) {
        if(!mx_strcmp(gui->send_to, group))
            mx_p_owned(gui->l_messages, message, sender);
            g_timeout_add(10, scroll, gui);
    }
    return 0;
}
