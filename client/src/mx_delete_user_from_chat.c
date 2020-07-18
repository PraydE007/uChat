#include "client.h"

static void init_json(json_object *jobj, const char *user_name, char *login,
                        t_s_glade *gui) {
    json_object *j_type = json_object_new_string("Delete_user_from_chat");
    json_object *j_login = json_object_new_string(login);
    json_object *j_user_name = json_object_new_string(user_name);
    json_object *j_chat_name = json_object_new_string(gui->send_to);
    json_object *j_key = json_object_new_string(gui->key);

    json_object_object_add(jobj,"Type", j_type);
    json_object_object_add(jobj,"Login", j_login);
    json_object_object_add(jobj,"Contact_login", j_user_name);
    json_object_object_add(jobj,"Chat_name", j_chat_name);
    json_object_object_add(jobj,"Security_key", j_key);
}

void mx_delete_user_from_chat(GtkButton *btn, gpointer data) {
    t_s_glade *gui = (t_s_glade *)data;
    char *send_data = NULL;
    const char *user_name = gtk_entry_get_text(GTK_ENTRY(gui->e_g_nickname));
    char *login = (char *)gtk_entry_get_text(GTK_ENTRY(gui->e_l_login));
    json_object *jobj = NULL;

    if (mx_strcmp(user_name, "")) {
        jobj = json_object_new_object();
        init_json(jobj, user_name, login, gui);
        send_data = (char *)json_object_to_json_string(jobj);
        send(gui->sockfd, send_data, strlen(send_data), 0);
    }
    (void)btn;
}
