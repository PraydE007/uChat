#include "client.h"

static int check_data(const char *pass, const char *mail,
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

static t_buf_registration init_registr(t_s_glade *gui) {
    t_buf_registration registr;

    registr.login = gtk_entry_get_text(GTK_ENTRY(gui->e_r_login));
    registr.mail = gtk_entry_get_text(GTK_ENTRY(gui->e_email));
    registr.pass0 = gtk_entry_get_text(GTK_ENTRY(gui->e_r_password));
    registr.pass1 = gtk_entry_get_text(GTK_ENTRY(gui->e_r_password2));
    registr.mobile = gtk_entry_get_text(GTK_ENTRY(gui->e_r_mobile));
    return registr;
}

static void init_json(json_object *jobj,t_buf_registration registr) {
    json_object *j_type = json_object_new_string("Registr");
    json_object *j_login = json_object_new_string(registr.login);
    json_object *j_passwd = json_object_new_string(registr.pass0);
    json_object *j_email = json_object_new_string(registr.mail);
    json_object *j_mobile = json_object_new_string(registr.mobile);
    json_object_object_add(jobj, "Type", j_type);
    json_object_object_add(jobj, "Login", j_login);
    json_object_object_add(jobj, "Passwd", j_passwd);
    json_object_object_add(jobj, "Email", j_email);
    json_object_object_add(jobj, "Mobile", j_mobile);
}

static void handle_errors(t_buf_registration registr, t_s_glade *gui) {
    if (check_data(registr.pass0, registr.mail, registr.login,
        registr.mobile) == 1)
            mx_show_dialog(gui->w_signup,
            "Incorrect email adress. Example - *********@****.***\n");
    else if (check_data(registr.pass0,
        registr.mail, registr.login, registr.mobile) == 4)
            mx_show_dialog(gui->w_signup,
            "Incorrect number. Example - +X (XXX) XXX - XXXX\n");
    else if (check_data(registr.pass0,
        registr.mail, registr.login, registr.mobile) == 2)
            mx_show_dialog(gui->w_signup,"Incorrect login.\n");
    else if (check_data(registr.pass0, registr.mail,
        registr.login, registr.mobile) == 3)
            mx_show_dialog(gui->w_signup,"Incorrect password.\n");
    else
        mx_show_dialog(gui->w_signup, "Passwords must be identical.\n");
}

void mx_registration(GtkButton *button, gpointer data) {
    t_s_glade *gui = (t_s_glade *)data;
    t_buf_registration registr = init_registr(gui);
    char *send_data = NULL;
    json_object *jobj = json_object_new_object();

    (void)button;
    if (!strcmp(registr.pass0, registr.pass1)
        && !check_data(registr.pass0, registr.mail,
        registr.login, registr.mobile)) {
        registr.pass0 = mx_hash((char *)registr.pass0);
        registr.pass1 = mx_hash((char *)registr.pass1);
        init_json(jobj, registr);
        send_data = (char *) json_object_to_json_string(jobj);
        send(gui->sockfd, send_data, strlen(send_data), 0);
    }
    else
        handle_errors(registr, gui);
}
