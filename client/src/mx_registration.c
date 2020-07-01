#include "client.h"

int check_data(const char *pass, const char *mail,
               const char *login, const char *number) {
    if (mx_check_mail(mail, 0))
        return 1;
    if (mx_check_login(login, 0))
        return 2;
    if (mx_check_pass(pass, 0))
        return 3;
    if (mx_check_number(number, 1))
        return 4;
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
    char buffer[2048];
    char *send_data = NULL;

    printf("LOGIN = %s\n", login);
    printf("MAIL = %s\n", mail);
    printf("PASS0 = %s\n", pass0);
    printf("PASS1 = %s\n", pass1);
    printf("CHECK_PASS = %d\n", check_data(pass0, mail, login, mobile));
    printf("NUMBER = %s\n", mobile);
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
        bzero(buffer, 2048);
        n = recv(gui->sockfd, buffer, 2048, 0);
        printf("BUFFER = %s\n", buffer);
    }
    else if (check_data(pass0, mail, login, mobile) == 1)
        printf("Incorrect email adress. Example - *********@****.***\n");
    else if (check_data(pass0, mail, login, mobile) == 2)
        printf("Incorrect login.\n");
    else if (check_data(pass0, mail, login, mobile) == 3)
        printf("Incorrect password.\n");
    else if (check_data(pass0, mail, login, mobile) == 4)
        printf("Incorrect number. Example - +X (XXX) XXX - XXXX\n");
    else
        printf("PAROLY NE SOVPADAYT BLEAT<3\n");
    if (!strcmp(buffer, "You have registered successfully!")) {
        gtk_window_get_position(mx_gw(gui->w_signup), &(gui->w_x), &(gui->w_y));
        gtk_widget_hide(gui->w_signup);
        gtk_widget_show_all(gui->w_signin);
        gtk_window_move(mx_gw(gui->w_signin), gui->w_x, gui->w_y + 22);
    }
}
