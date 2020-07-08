#include "client.h"

void mx_find_user(GtkButton *button, gpointer data) {
    t_s_glade *gui = (t_s_glade *)data;
    const gchar *name = gtk_entry_get_text(GTK_ENTRY(gui->e_find));
    const char *login = gtk_entry_get_text(GTK_ENTRY(gui->e_l_login));
    char *send_data = NULL;
    json_object *jobj = json_object_new_object();
    json_object *j_type = json_object_new_string("Add_contact");
    json_object *j_login = json_object_new_string(login);
    json_object *j_passwd = json_object_new_string(name);
    json_object *j_key = json_object_new_string("cdef9e974ae775ea9b1472cedb108607127607e538b5c1ff8f9e46123");
    json_object_object_add(jobj,"Type", j_type);
    json_object_object_add(jobj,"Login", j_login);
    json_object_object_add(jobj,"Contact_login", j_passwd);
    json_object_object_add(jobj,"Security_key", j_key);

    send_data = (char *)json_object_to_json_string(jobj);
    if (mx_strcmp(name, ""))
        send(gui->sockfd, send_data, strlen(send_data), 0);
    (void)button;
}
