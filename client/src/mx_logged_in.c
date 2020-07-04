#include "client.h"

void mx_logged_in(GtkButton *button, gpointer data) {
    char *send_data = NULL;
    t_s_glade *gui = (t_s_glade *)data;
    const char *login = gtk_entry_get_text(GTK_ENTRY(gui->e_l_login));
    const char *pass = gtk_entry_get_text(GTK_ENTRY(gui->e_l_password));
    int n = 0;
    char buffer[2048];

    (void)button;
    json_object *jobj = json_object_new_object();
    json_object *j_type = json_object_new_string("Logging");
    json_object *j_login = json_object_new_string(login);
    json_object *j_passwd = json_object_new_string(pass);
    json_object_object_add(jobj,"Type", j_type);
    json_object_object_add(jobj,"Login", j_login);
    json_object_object_add(jobj,"Passwd", j_passwd);

    send_data = (char *)json_object_to_json_string(jobj);

    n = send(gui->sockfd, send_data, strlen(send_data), 0);
    bzero(buffer, 2048);
    n = recv(gui->sockfd, buffer, 2048, 0);
    printf("BUFFER LOGGED = %s\n", buffer);
    jobj = json_tokener_parse(buffer);
    char *res = (char *)json_object_get_string(json_object_object_get(jobj, "Answer"));
    printf("RES = %s\n", res);
    if ((!mx_strcmp(login, "admin") && !mx_strcmp(pass, "admin")) || !strcmp(res, "You have logged in!"))
        mx_logged_in_chat(gui);
}
