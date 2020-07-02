#include "client.h"

static char *json_to_str(json_object *jobj, char *key) {
    char *value = NULL;

    value = (char *)json_object_get_string(json_object_object_get(jobj, key));
    return value;
}

static t_buff_getchar_prof init_buff(t_s_glade *gui) {
    t_buff_getchar_prof buff_getchar_prof;

    buff_getchar_prof.login = (char *)gtk_entry_get_text(GTK_ENTRY(gui->e_p_login));
    buff_getchar_prof.email = (char *)gtk_entry_get_text(GTK_ENTRY(gui->e_p_email));
    buff_getchar_prof.number = (char *)gtk_entry_get_text(GTK_ENTRY(gui->e_p_number));
    return buff_getchar_prof;
}

static void set_user_fields(t_s_glade *gui, t_buff_getchar_prof buff_getchar_prof) {
    gtk_entry_set_text(GTK_ENTRY(gui->e_p_login), buff_getchar_prof.login);
    gtk_entry_set_text(GTK_ENTRY(gui->e_p_email), buff_getchar_prof.email);
    gtk_entry_set_text(GTK_ENTRY(gui->e_p_number), buff_getchar_prof.number);
}

static void change_window(t_s_glade *gui) {
    gtk_window_get_position(mx_gw(gui->w_chat), &(gui->w_x), &(gui->w_y));
    gtk_widget_hide(gui->w_chat);
    gtk_widget_show_all(gui->w_profile);
    gtk_window_move(mx_gw(gui->w_profile), gui->w_x, gui->w_y + 22);
}

void mx_open_profile(GtkButton *button, gpointer data) {
    t_s_glade *gui = (t_s_glade *)data;
    t_buff_getchar_prof buff_getchar_prof = init_buff(gui);
    int n = 0;
    char buffer[MX_MAX_BYTES];
    char *send_data = NULL;

    (void)button;
    json_object *jobj = json_object_new_object();
    json_object *j_type = json_object_new_string("Get_Profile");
    json_object_object_add(jobj,"Type", j_type);
    send_data = (char *)json_object_to_json_string(jobj);
    n = send(gui->sockfd, send_data, strlen(send_data), 0);
    bzero(buffer, MX_MAX_BYTES);
    n = recv(gui->sockfd, buffer, MX_MAX_BYTES, 0);
    json_object *j_taked = json_tokener_parse(buffer);
    buff_getchar_prof.login = json_to_str(j_taked, "Login");
    buff_getchar_prof.email = json_to_str(j_taked, "Email");
    buff_getchar_prof.number = json_to_str(j_taked, "Number");
    json_object_put(jobj);
    set_user_fields(gui, buff_getchar_prof);
    change_window(gui);
}
