#include "client.h"

static const char *json_to_str(json_object *jobj, char *key) {
    const char *value = NULL;

    value = json_object_get_string(json_object_object_get(jobj, key));
    return value;
}

gboolean mx_success_change_profile(void *data) {
    t_s_glade *gui = (t_s_glade *)data;
    json_object *jobj = json_tokener_parse(gui->recv_data);

    char *login = (char *)json_to_str(jobj, "Login");
    char *email = (char *)json_to_str(jobj, "Email");
    char *mobile = (char *)json_to_str(jobj, "Mobile");

    //gtk_entry_set_text(GTK_ENTRY(gui->e_l_login), login);
    gtk_entry_set_text(GTK_ENTRY(gui->e_p_login), login);
    gtk_entry_set_text(GTK_ENTRY(gui->e_p_email), email);
    gtk_entry_set_text(GTK_ENTRY(gui->e_p_number), mobile);

    return 0;
}
