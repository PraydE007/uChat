#include "client.h"

void mx_open_chat(GtkListBox *box, GtkListBoxRow *row, gpointer data) {
    const char *send_data = NULL;
    t_s_glade *gui = (t_s_glade *)data;
    GtkWidget *grid = gtk_bin_get_child(GTK_BIN(row));
    GtkWidget *chat_name = gtk_grid_get_child_at(GTK_GRID(grid), 1, 0);
    const char *login = gtk_entry_get_text(GTK_ENTRY(gui->e_l_login));
    json_object *j_type = NULL;

    (void)box;
    gui->send_to = strdup(gtk_label_get_text(GTK_LABEL(chat_name)));
    if(gui->send_to) {
        json_object *jobj = json_object_new_object();
        j_type = json_object_new_string("Chat");
        json_object *j_login = json_object_new_string(login);
        json_object *j_chat_name = json_object_new_string(gui->send_to);
        json_object *j_key = json_object_new_string(gui->key);
        json_object_object_add(jobj,"Type", j_type);
        json_object_object_add(jobj,"Login", j_login);
        json_object_object_add(jobj,"Chat_name", j_chat_name);
        json_object_object_add(jobj,"Security_key", j_key);
        send_data = json_object_to_json_string(jobj);
        printf("SEND_DATA :%s\n", send_data);
        send(gui->sockfd, send_data, strlen(send_data), 0);
        mx_clear_container(gui->l_messages);
        gtk_widget_show(gui->b_c_pad);
        // gtk_bin_get_child(GTK_BIN(gtk_list_box_get_selected_row(GTK_LIST_BOX(listbox))));
    }
}
