#include "client.h"

static int check_data(const char *pass0) {
    if (mx_check_pass(pass0, 0))
        return 3;
    else
        return 0;
}

void mx_change_pass(GtkButton *button, gpointer data) {
    t_s_glade *gui = (t_s_glade *)data;
    char *login = (char *)gtk_entry_get_text(GTK_ENTRY(gui->e_l_login));
    char *passwd = (char *)gtk_entry_get_text(GTK_ENTRY(gui->e_l_password));
    const char *old_pass = gtk_entry_get_text(GTK_ENTRY(gui->e_p_oldpass));
    const char *pass0 = gtk_entry_get_text(GTK_ENTRY(gui->e_p_newpass1));
    const char *pass1 = gtk_entry_get_text(GTK_ENTRY(gui->e_p_newpass2));

    int n = 0;
    char *send_data = NULL;
    json_object *jobj = json_object_new_object();
    (void)button;
    if (!strcmp(pass0, pass1) && !check_data(pass0)) {
        json_object *j_type = json_object_new_string("Change_passwd");
        json_object *j_login = json_object_new_string(login);
        json_object *j_old_pass = json_object_new_string(old_pass);
        json_object *j_passwd = json_object_new_string(pass0);
        json_object *j_security_key = json_object_new_string(gui->key);
        json_object_object_add(jobj, "Type", j_type);
        json_object_object_add(jobj, "Login", j_login);
        json_object_object_add(jobj, "Passwd", j_old_pass);
        json_object_object_add(jobj, "New_passwd", j_passwd);
        json_object_object_add(jobj, "Security_key", j_security_key);

        send_data = (char *) json_object_to_json_string(jobj);
        printf("SEND_DATA = %s\n", send_data);
        n = send(gui->sockfd, send_data, strlen(send_data), 0);
    }
    else if (check_data(pass0) == 3) {
        mx_show_dialog(gui->w_profile, "Incorrect password\n");
    }
    else if (check_data(pass0) == 0) {
        mx_show_dialog(gui->w_profile, "Password mismatch\n");
    }
    if (strcmp(passwd, old_pass) != 0){
        mx_show_dialog(gui->w_profile, "Wrong password!\n");
    }
    gtk_entry_set_text(GTK_ENTRY(gui->e_p_oldpass), "");
    gtk_entry_set_text(GTK_ENTRY(gui->e_p_newpass1), "");
    gtk_entry_set_text(GTK_ENTRY(gui->e_p_newpass2), "");
}
