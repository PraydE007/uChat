#include "client.h"

static int check_data(const char *pass0) {
    if (mx_check_pass(pass0, 0))
        return 3;
    else
        return 0;
}

static t_buf_change_pass buf_change_pass(t_s_glade *gui) {
    t_buf_change_pass change_pass;

    change_pass.login = (char *)gtk_entry_get_text(GTK_ENTRY(gui->e_l_login));
    change_pass.passwd =
        (char *)gtk_entry_get_text(GTK_ENTRY(gui->e_l_password));
    change_pass.old_pass = gtk_entry_get_text(GTK_ENTRY(gui->e_p_oldpass));
    change_pass.pass0 = gtk_entry_get_text(GTK_ENTRY(gui->e_p_newpass1));
    change_pass.pass1 = gtk_entry_get_text(GTK_ENTRY(gui->e_p_newpass2));
    return change_pass;
}

static void init_json(json_object *jobj, t_buf_change_pass change_pass, t_s_glade *gui) {
    json_object *j_type = json_object_new_string("Change_passwd");
    json_object *j_login = json_object_new_string(change_pass.login);
    json_object *j_old_pass = json_object_new_string(change_pass.old_pass);
    json_object *j_passwd = json_object_new_string(change_pass.pass0);
    json_object *j_security_key = json_object_new_string(gui->key);

    json_object_object_add(jobj, "Type", j_type);
    json_object_object_add(jobj, "Login", j_login);
    json_object_object_add(jobj, "Passwd", j_old_pass);
    json_object_object_add(jobj, "New_passwd", j_passwd);
    json_object_object_add(jobj, "Security_key", j_security_key);
}

static void set_text_pass(t_s_glade *gui) {
    gtk_entry_set_text(GTK_ENTRY(gui->e_p_oldpass), "");
    gtk_entry_set_text(GTK_ENTRY(gui->e_p_newpass1), "");
    gtk_entry_set_text(GTK_ENTRY(gui->e_p_newpass2), "");
}

void mx_change_pass(GtkButton *button, gpointer data) {
    t_s_glade *gui = (t_s_glade *)data;
    t_buf_change_pass change_pass = buf_change_pass(gui);
    int n = 0;
    change_pass.send_data = NULL;
    json_object *jobj = json_object_new_object();

    (void)button;
    if (!strcmp(change_pass.pass0, change_pass.pass1)
        && !check_data(change_pass.pass0)) {
        init_json(jobj, change_pass, gui);
        change_pass.send_data = (char *) json_object_to_json_string(jobj);
        n = send(gui->sockfd, change_pass.send_data, strlen(change_pass.send_data), 0);
    }
    else if (check_data(change_pass.pass0) == 3)
        mx_show_dialog(gui->w_profile, "Incorrect password\n");
    else if (check_data(change_pass.pass0) == 0)
        mx_show_dialog(gui->w_profile, "Password mismatch\n");
    if (strcmp(change_pass.passwd, change_pass.old_pass) != 0)
        mx_show_dialog(gui->w_profile, "Wrong password!\n");
    set_text_pass(gui);
}
