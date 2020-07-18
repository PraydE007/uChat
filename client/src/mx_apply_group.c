#include "client.h"

static t_buf_apply_group init_apply_group(t_s_glade *gui) {
    t_buf_apply_group buf_apply_group;

    buf_apply_group.send_data = NULL;
    buf_apply_group.new_name =
        gtk_entry_get_text(GTK_ENTRY(gui->e_group_name));
    buf_apply_group.login = gtk_entry_get_text(GTK_ENTRY(gui->e_l_login));
    return buf_apply_group;
}

static void init_json(json_object *jobj,
                    t_buf_apply_group buf_apply_group,
                    t_s_glade *gui) {
    json_object *j_type = json_object_new_string("Change_chat");
    json_object *j_login = json_object_new_string(buf_apply_group.login);
    json_object *j_chat_name = json_object_new_string(gui->send_to);
    json_object *j_new_chat_name =
        json_object_new_string(buf_apply_group.new_name);
    json_object *j_key = json_object_new_string(gui->key);
    json_object_object_add(jobj,"Type", j_type);
    json_object_object_add(jobj,"Login", j_login);
    json_object_object_add(jobj,"Chat_name", j_chat_name);
    json_object_object_add(jobj,"New_chat_name", j_new_chat_name);
    json_object_object_add(jobj,"Security_key", j_key);
}

void mx_apply_group(GtkButton *btn, gpointer data) {
    t_s_glade *gui = (t_s_glade *)data;
    t_buf_apply_group buf_apply_group = init_apply_group(gui);
    json_object *jobj = NULL;

    (void)btn;
    jobj = json_object_new_object();
    init_json(jobj, buf_apply_group, gui);
    buf_apply_group.send_data = (char *)json_object_to_json_string(jobj);
    printf("SEND_DATA :%s\n", buf_apply_group.send_data);
    send(gui->sockfd,
        buf_apply_group.send_data, strlen(buf_apply_group.send_data), 0);
}
