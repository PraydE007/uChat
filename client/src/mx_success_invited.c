#include "client.h"

static const char *json_to_str(json_object *jobj, char *key) {
    const char *value = NULL;

    value = json_object_get_string(json_object_object_get(jobj, key));
    return value;
}

gboolean mx_success_invited(void *data) {
    t_s_glade *gui = (t_s_glade *)data;
    json_object *jobj = json_tokener_parse(gui->recv_data);

    const char *inviter = json_to_str(jobj, "Chat_name");
    mx_push_chat(gui->l_chats, inviter);
    return 0;
}
