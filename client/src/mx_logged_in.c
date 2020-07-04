#include "client.h"

void mx_logged_in(GtkButton *button, gpointer data) {
    char *send_data = NULL;
    t_s_glade *gui = (t_s_glade *)data;
    const char *login = gtk_entry_get_text(GTK_ENTRY(gui->e_l_login));
    const char *pass = gtk_entry_get_text(GTK_ENTRY(gui->e_l_password));
    int n = 0;

    (void)button;
    json_object *jobj = json_object_new_object();
    json_object *j_type = json_object_new_string("Logging");
    json_object *j_login = json_object_new_string(login);
    json_object *j_passwd = json_object_new_string(pass);
    json_object_object_add(jobj,"Type", j_type);
    json_object_object_add(jobj,"Login", j_login);
    json_object_object_add(jobj,"Passwd", j_passwd);
    send_data = (char *)json_object_to_json_string(jobj);
    n = send(gui->sockfd, send_data, strlen(send_data), 0);
}
