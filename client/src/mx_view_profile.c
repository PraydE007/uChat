#include "client.h"

void mx_view_profile(GtkButton *btn, gpointer data) {
    t_s_glade *gui = (t_s_glade *)data;
    char *login = (char *)gtk_entry_get_text(GTK_ENTRY(gui->e_l_login));
    const char *send_data = NULL;

    if(gui->if_contact == 1) {
        json_object *jobj = json_object_new_object();
        json_object *j_type = json_object_new_string("Get_contact_profile");
        json_object *j_login = json_object_new_string(login);
        json_object *j_contact_login = json_object_new_string(gui->send_to);
        json_object *j_key = json_object_new_string(gui->key);
        json_object_object_add(jobj,"Type", j_type);
        json_object_object_add(jobj,"Login", j_login);
        json_object_object_add(jobj,"Contact_login", j_contact_login);
        json_object_object_add(jobj,"Security_key", j_key);
        send_data = json_object_to_json_string(jobj);
        printf("SEND_DATA :%s\n", send_data);
        send(gui->sockfd, send_data, strlen(send_data), 0);
        (void)btn;
    }

    (void)btn;
}
