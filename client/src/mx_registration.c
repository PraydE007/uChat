#include "client.h"

int check_data(const char *pass, const char *mail,
               const char *login, const char *number) {
    if (mx_check_mail(mail, 0))
        return 1;
    if (mx_check_number(number, 1))
        return 4;
    if (mx_check_login(login, 0))
        return 2;
    if (mx_check_pass(pass, 0))
        return 3;
    else
        return 0;
}

void mx_registration(GtkButton *button, gpointer data) {
    t_s_glade *gui = (t_s_glade *)data;
    const char *login = gtk_entry_get_text(GTK_ENTRY(gui->e_r_login));
    const char *mail = gtk_entry_get_text(GTK_ENTRY(gui->e_email));
    const char *pass0 = gtk_entry_get_text(GTK_ENTRY(gui->e_r_password));
    const char *pass1 = gtk_entry_get_text(GTK_ENTRY(gui->e_r_password2));
    const char *mobile = gtk_entry_get_text(GTK_ENTRY(gui->e_r_mobile));

    int n = 0;
    char *send_data = NULL;

    (void)button;
    if (!strcmp(pass0, pass1) && !check_data(pass0, mail, login, mobile)) {
        json_object *jobj = json_object_new_object();
        json_object *j_type = json_object_new_string("Registr");
        json_object *j_login = json_object_new_string(login);
        json_object *j_passwd = json_object_new_string(pass0);
        json_object *j_email = json_object_new_string(mail);
        json_object *j_mobile = json_object_new_string(mobile);
        json_object_object_add(jobj, "Type", j_type);
        json_object_object_add(jobj, "Login", j_login);
        json_object_object_add(jobj, "Passwd", j_passwd);
        json_object_object_add(jobj, "Email", j_email);
        json_object_object_add(jobj, "Mobile", j_mobile);

        send_data = (char *) json_object_to_json_string(jobj);

        printf("SEND_DATA = %s\n", send_data);
        n = send(gui->sockfd, send_data, strlen(send_data), 0);
    }
    else if (check_data(pass0, mail, login, mobile) == 1)
        mx_show_dialog(gui->w_signup, "Incorrect email adress. Example - *********@****.***\n");
    else if (check_data(pass0, mail, login, mobile) == 4)
        mx_show_dialog(gui->w_signup,"Incorrect number. Example - +X (XXX) XXX - XXXX\n");
    else if (check_data(pass0, mail, login, mobile) == 2)
        mx_show_dialog(gui->w_signup,"Incorrect login.\n");
    else if (check_data(pass0, mail, login, mobile) == 3)
        mx_show_dialog(gui->w_signup,"Incorrect password.\n");
    else
        mx_show_dialog(gui->w_signup, "Passwords must be identical.\n");
}
