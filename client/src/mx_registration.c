#include "client.h"

int check_mail_else_body(const char *mail, int i) {
    i++;
    if (isalpha(mail[i]) || isdigit(mail[i])) {
        while (isalpha(mail[i]) || isdigit(mail[i]))
            i++;
        if (mail[i] != '.')
            return 1;
        else {
            i++;
            if (isalpha(mail[i]) || isdigit(mail[i])) {
                while (isalpha(mail[i]) || isdigit(mail[i]))
                    i++;
                if (i == mx_strlen(mail))
                    return 0;
            }
        }
    }
    return 1;
}

int check_mail(const char *mail, int i) {
    if (isalpha(mail[0]) || isdigit(mail[0]) || mail[0] == '.' || mail[0] == '_') {
        while (isalpha(mail[i]) || isdigit(mail[i]) || mail[i] == '.' || mail[i] == '_')
            i++;
        if (mail[i] != '@')
            return 1;
        else
            return check_mail_else_body(mail, i);
    }
    return 1;
}

int check_login(const char *login, int j) {
    if (isalpha(login[0]) || isdigit(login[0])) {
        for (; login[j]; j++) {
            if (!isalpha(login[j]) && !isdigit(login[j]))
                return 1;
        }
        return 0;
    }
    return 1;
}

int check_pass(const char *pass, int j) {
    if (isalpha(pass[0]) || isdigit(pass[0])) {
        for (; pass[j]; j++) {
            if (!isalpha(pass[j]) && !isdigit(pass[j]))
                return 1;
        }
        return 0;
    }
    return 1;
}

int check_data(const char *pass, const char *mail, const char *login) {
    if (check_mail(mail, 0))
        return 1;
    if (check_login(login, 0))
        return 2;
    if (check_pass(pass, 0))
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
    int n = 0;
    char buffer[2048];
    char *send_data = NULL;

    printf("LOGIN = %s\n", login);
    printf("MAIL = %s\n", mail);
    printf("PASS0 = %s\n", pass0);
    printf("PASS1 = %s\n", pass1);
    printf("CHECK_PASS = %d\n", check_data(pass0, mail, login));
    (void)button;
    if (!strcmp(pass0, pass1) && !check_data(pass0, mail, login)) {
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

        printf("SEND_DATA = %s\n", send_data);
        n = send(gui->sockfd, send_data, strlen(send_data), 0);
        bzero(buffer, 2048);
        n = recv(gui->sockfd, buffer, 2048, 0);
        printf("BUFFER = %s\n", buffer);
    }
    else if (check_data(pass0, mail, login) == 1)
        printf("Incorrect email adress. Example - *********@****.***\n");
    else if (check_data(pass0, mail, login) == 2)
        printf("Incorrect login.\n");
    else if (check_data(pass0, mail, login) == 3)
        printf("Incorrect password.\n");
    else
        printf("PAROLY NE SOVPADAYT BLEAT<3\n");
    if (!strcmp(buffer, "You have registered successfully!")) {
        gtk_widget_hide(gui->w_signup);
        gtk_widget_hide(gui->w_signin);
        gtk_widget_hide(gui->w_settings);
        gtk_widget_show_all(gui->w_signin);
    }
}
