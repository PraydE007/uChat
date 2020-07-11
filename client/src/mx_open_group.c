#include "client.h"

void mx_open_group(GtkButton *btn, gpointer data) {
    t_s_glade *gui = (t_s_glade *)data;

    const gchar *group_name = gtk_entry_get_text(GTK_ENTRY(gui->e_find));
    const char *send_data = NULL;
    char *login = (char *)gtk_entry_get_text(GTK_ENTRY(gui->e_l_login));

    (void)btn;
        if (mx_strcmp(group_name, "")) {
            json_object *jobj = json_object_new_object();
            json_object *j_type = json_object_new_string("Create_chat");
            json_object *j_login = json_object_new_string(login);
            json_object *j_chat_name = json_object_new_string(group_name);
            json_object *j_key = json_object_new_string(gui->key);
            json_object_object_add(jobj,"Type", j_type);
            json_object_object_add(jobj,"Login", j_login);
            json_object_object_add(jobj,"Chat_name", j_chat_name);
            json_object_object_add(jobj,"Security_key", j_key);
            send_data = (char *)json_object_to_json_string(jobj);
            printf("SEND_DATA :%s\n", send_data);
            send(gui->sockfd, send_data, strlen(send_data), 0);
        }
        // else {
        // OPEN GROUP CONTROL FOR SELECTED GROUP
        // gtk_window_get_position(mx_gw(gui->w_chat), &(gui->w_x), &(gui->w_y));
        // gtk_widget_hide(gui->w_chat);
        // gtk_widget_show_all(gui->w_group);
        // gtk_window_move(mx_gw(gui->w_group), gui->w_x, gui->w_y + 22);
    // }
}
