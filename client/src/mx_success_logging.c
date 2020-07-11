#include "client.h"

static const char *json_to_str(json_object *jobj, char *key) {
    const char *value = NULL;

    value = json_object_get_string(json_object_object_get(jobj, key));
    return value;
}

gboolean mx_success_logging(void *data) {
    t_s_glade *gui = (t_s_glade *)data;
    json_object *jobj = json_tokener_parse(gui->recv_data);
    gui->key = strdup(json_to_str(jobj, "Security_key"));
    gui->contacts = mx_strsplit(json_to_str(jobj, "Contacts"), ',');
    gui->if_contact = false;
    mx_render_contacts(gui);
    mx_logged_in_chat(gui);
    return 0;
}
