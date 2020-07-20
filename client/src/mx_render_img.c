#include "client.h"


static const char *json_to_str(json_object *jobj, char *key) {
    const char *value = NULL;

    value = json_object_get_string(json_object_object_get(jobj, key));
    return value;
}

gboolean mx_render_img(void *data) {
    t_s_glade *gui = (t_s_glade *) data;
    json_object *jobj = json_tokener_parse(gui->recv_data);
    const char *sender = json_to_str(jobj, "Sender");

    mx_p_owned_img(gui->l_messages, gui->file_path, sender);
    return 0;
}
