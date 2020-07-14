#include "client.h"

void mx_apply_group(GtkButton *btn, gpointer data) {
    t_s_glade *gui = (t_s_glade *)data;
    const char *send_data = NULL;
    const char *new_name = gtk_entry_get_text(GTK_ENTRY(gui->e_group_name));
    const char *login = gtk_entry_get_text(GTK_ENTRY(gui->e_l_login));

    (void)btn;
    json_object *jobj = json_object_new_object();
    json_object *j_type = json_object_new_string("Change_chat");
    json_object *j_login = json_object_new_string(login);
    json_object *j_chat_name = json_object_new_string(gui->send_to);
    json_object *j_new_chat_name = json_object_new_string(new_name);
    json_object *j_key = json_object_new_string(gui->key);
    json_object_object_add(jobj,"Type", j_type);
    json_object_object_add(jobj,"Login", j_login);
    json_object_object_add(jobj,"Chat_name", j_chat_name);
    json_object_object_add(jobj,"New_chat_name", j_new_chat_name);
    json_object_object_add(jobj,"Security_key", j_key);
    send_data = (char *)json_object_to_json_string(jobj);
    printf("SEND_DATA :%s\n", send_data);
    send(gui->sockfd, send_data, strlen(send_data), 0);

}
