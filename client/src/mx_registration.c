#include "client.h"

void mx_registration(GtkButton *button, gpointer data) {
    t_s_glade *gui = (t_s_glade *)data;
    const char *login = gtk_entry_get_text(GTK_ENTRY(gui->e_r_login));
    const char *mail = gtk_entry_get_text(GTK_ENTRY(gui->e_email));
    const char *pass0 = gtk_entry_get_text(GTK_ENTRY(gui->e_r_password));
    const char *pass1 = gtk_entry_get_text(GTK_ENTRY(gui->e_r_password2));
    int n = 0;
    char buffer[2048];
    char *send_data = NULL;

    (void)button;
    if (!strcmp(pass0, pass1)) {
        json_object *jobj = json_object_new_object();
        json_object *j_type = json_object_new_string("Registr");
        json_object *j_login = json_object_new_string(login);
        json_object *j_passwd = json_object_new_string(pass0);
        json_object *j_email = json_object_new_string(mail);
        json_object_object_add(jobj, "Type", j_type);
        json_object_object_add(jobj, "Login", j_login);
        json_object_object_add(jobj, "Passwd", j_passwd);
        json_object_object_add(jobj, "Email", j_email);

        send_data = (char *) json_object_to_json_string(jobj);

        n = send(gui->sockfd, send_data, strlen(send_data), 0);
        bzero(buffer, 2048);
        n = recv(gui->sockfd, buffer, 2048, 0);
        printf("BUFFER = %s\n", buffer);
    }
    else
        printf("PAROLY NE SOVPADAYT BLEAT<3\n");
    if (!strcmp(buffer, "You have registered successfully!")) {
        gtk_widget_hide(gui->w_signup);
        gtk_widget_hide(gui->w_signin);
        gtk_widget_hide(gui->w_settings);
        gtk_widget_show_all(gui->w_signin);
    }
}
