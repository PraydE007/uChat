#include "client.h"

static int check_data(const char *pass0) {
    if (mx_check_pass(pass0, 0))
        return 3;
    else
        return 0;
}

void mx_change_pass(GtkButton *button, gpointer data) {
    t_s_glade *gui = (t_s_glade *)data;
    const char *old_pass = gtk_entry_get_text(GTK_ENTRY(gui->e_p_oldpass));
    const char *pass0 = gtk_entry_get_text(GTK_ENTRY(gui->e_p_newpass1));
    const char *pass1 = gtk_entry_get_text(GTK_ENTRY(gui->e_p_newpass2));

    int n = 0;
    char buffer[2048];
    char *send_data = NULL;

    printf("OLD_PASS = %s\n", old_pass);
    printf("PASS0 = %s\n", pass0);
    printf("PASS1 = %s\n", pass1);
    printf("CHECK_PASS = %d\n", check_data(pass0));
    (void)button;
    if (!strcmp(pass0, pass1) && !check_data(pass0)) {
        json_object *jobj = json_object_new_object();
        json_object *j_security_key = json_object_new_string("cdef9e974ae775ea9b1472cedb108607127607e538b5c1ff8f9e46123");
        json_object *j_type = json_object_new_string("Change_passwd");
        json_object *j_old_pass = json_object_new_string(old_pass);
        json_object *j_passwd = json_object_new_string(pass0);
        json_object_object_add(jobj, "Type", j_type);
        json_object_object_add(jobj, "Security_key", j_security_key);
        json_object_object_add(jobj, "Passwd", j_old_pass);
        json_object_object_add(jobj, "New_passwd", j_passwd);

        send_data = (char *) json_object_to_json_string(jobj);

        printf("SEND_DATA = %s\n", send_data);
        n = send(gui->sockfd, send_data, strlen(send_data), 0);
        bzero(buffer, 2048);
        n = recv(gui->sockfd, buffer, 2048, 0);
        printf("BUFFER CHANGE PASS = %s\n", buffer);
    }
    else if (check_data(pass0) == 3)
        mx_show_dialog(gui->w_profile, "Incorrect password\n");
    else
        mx_show_dialog(gui->w_profile, "PAROLY NE SOVPADAYT BLEAT<3\n");
    if (!strcmp(buffer, "You have registered successfully!")) {
        mx_show_dialog(gui->w_profile, "Password changed!\n");
        gtk_window_get_position(mx_gw(gui->w_profile), &(gui->w_x), &(gui->w_y));
        gtk_widget_hide(gui->w_password);
        gtk_widget_show_all(gui->w_profile);
        gtk_window_move(mx_gw(gui->w_profile), gui->w_x, gui->w_y + 22);
    }
}
