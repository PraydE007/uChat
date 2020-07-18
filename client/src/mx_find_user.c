#include "client.h"

static t_buf_find_user init_find_user(t_s_glade *gui) {
    t_buf_find_user find_user;

    find_user.name = gtk_entry_get_text(GTK_ENTRY(gui->e_find));
    find_user.login = gtk_entry_get_text(GTK_ENTRY(gui->e_l_login));
    find_user.send_data = NULL;
    return find_user;
}

static void init_json(json_object *jobj, t_buf_find_user find_user,
                    t_s_glade *gui) {
    json_object *j_type = json_object_new_string("Add_contact");
    json_object *j_login = json_object_new_string(find_user.login);
    json_object *j_passwd = json_object_new_string(find_user.name);
    json_object *j_key = json_object_new_string(gui->key);

    json_object_object_add(jobj,"Type", j_type);
    json_object_object_add(jobj,"Login", j_login);
    json_object_object_add(jobj,"Contact_login", j_passwd);
    json_object_object_add(jobj,"Security_key", j_key);
}

void mx_find_user(GtkButton *button, gpointer data) {
    t_s_glade *gui = (t_s_glade *)data;
    t_buf_find_user find_user = init_find_user(gui);
    json_object *jobj = json_object_new_object();

    init_json(jobj, find_user, gui);
    find_user.send_data = (char *)json_object_to_json_string(jobj);
    if (mx_strcmp(find_user.name, ""))
        send(gui->sockfd, find_user.send_data, strlen(find_user.send_data), 0);
    (void)button;
}
