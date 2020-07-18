#include "client.h"

static void init_json(json_object *jobj, char *login, t_s_glade *gui) {
    json_object *j_type = json_object_new_string("Delete_contact");
    json_object *j_login = json_object_new_string(login);
    json_object *j_contact_login = json_object_new_string(gui->send_to);
    json_object *j_key = json_object_new_string(gui->key);

    json_object_object_add(jobj,"Type", j_type);
    json_object_object_add(jobj,"Login", j_login);
    json_object_object_add(jobj,"Contact_login", j_contact_login);
    json_object_object_add(jobj,"Security_key", j_key);
}

static void init_second_json(json_object *jobj, char *login, t_s_glade *gui) {
    json_object *j_type = json_object_new_string("Delete_chat");
    json_object *j_login = json_object_new_string(login);
    json_object *j_contact_login = json_object_new_string(gui->send_to);
    json_object *j_key = json_object_new_string(gui->key);

    json_object_object_add(jobj,"Type", j_type);
    json_object_object_add(jobj,"Login", j_login);
    json_object_object_add(jobj,"Chat_name", j_contact_login);
    json_object_object_add(jobj,"Security_key", j_key);
}

void mx_delete_contact(GtkButton *btn, gpointer data) {
    t_s_glade *gui = (t_s_glade *)data;
    char *login = (char *)gtk_entry_get_text(GTK_ENTRY(gui->e_l_login));
    const char *send_data = NULL;
    json_object *jobj = json_object_new_object();

    if (gui->if_contact == 1) {
        init_json(jobj, login, gui);
        send_data = json_object_to_json_string(jobj);
        send(gui->sockfd, send_data, strlen(send_data), 0);
    }
    else if (gui->if_contact == 0) {
        init_second_json(jobj, login, gui);
        send_data = json_object_to_json_string(jobj);
        send(gui->sockfd, send_data, strlen(send_data), 0);
    }
    (void)btn;
}
