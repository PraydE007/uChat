#include "client.h"

static void init_json(json_object *jobj, t_s_glade *gui) {
    json_object *j_type = json_object_new_string("Get_profile");
    json_object *j_login = json_object_new_string(
        (char *)gtk_entry_get_text(GTK_ENTRY(gui->e_l_login)));
    json_object *j_key = json_object_new_string(gui->key);
    json_object_object_add(jobj,"Type", j_type);
    json_object_object_add(jobj,"Login", j_login);
    json_object_object_add(jobj,"Security_key", j_key);
}

void mx_open_profile(GtkButton *button, gpointer data) {
    t_s_glade *gui = (t_s_glade *)data;
    int n = 0;
    char *send_data = NULL;
    json_object *jobj = json_object_new_object();

    (void)button;
    init_json(jobj, gui);
    send_data = (char *)json_object_to_json_string(jobj);
    n = send(gui->sockfd, send_data, strlen(send_data), 0);
}
