#include "client.h"

static void init_json(json_object *jobj,
                    t_buf_add_user_to_group add_user_to_group,
                    t_s_glade *gui) {
        json_object *j_type = json_object_new_string("Add_user_to_chat");
        json_object *j_login = json_object_new_string(add_user_to_group.login);
        json_object *j_user_name =
            json_object_new_string(add_user_to_group.user_name);
        json_object *j_chat_name = json_object_new_string(gui->send_to);
        json_object *j_key = json_object_new_string(gui->key);

        json_object_object_add(jobj,"Type", j_type);
        json_object_object_add(jobj,"Login", j_login);
        json_object_object_add(jobj,"Contact_login", j_user_name);
        json_object_object_add(jobj,"Chat_name", j_chat_name);
        json_object_object_add(jobj,"Security_key", j_key);
}

static t_buf_add_user_to_group init_add_user_to_group(t_s_glade *gui) {
    t_buf_add_user_to_group add_user_to_group;

    add_user_to_group.send_data = NULL;
    add_user_to_group.user_name =
        gtk_entry_get_text(GTK_ENTRY(gui->e_g_nickname));
    add_user_to_group.login =
        (char *)gtk_entry_get_text(GTK_ENTRY(gui->e_l_login));
    return add_user_to_group;
}

void mx_add_user_to_group(GtkButton *btn, gpointer data) {
    t_s_glade *gui = (t_s_glade *)data;
    t_buf_add_user_to_group add_user_to_group = init_add_user_to_group(gui);
    json_object *jobj = NULL;

    if (mx_strcmp(add_user_to_group.user_name, "")) {
        jobj = json_object_new_object();
        init_json(jobj, add_user_to_group, gui);
        add_user_to_group.send_data =
            (char *)json_object_to_json_string(jobj);
        send(gui->sockfd, add_user_to_group.send_data,
            strlen(add_user_to_group.send_data), 0);
    }
    (void)btn;
}
