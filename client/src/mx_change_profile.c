#include "client.h"

static void mx_change_window(t_s_glade *gui) {
    gtk_window_get_position(mx_gw(gui->w_profile), &(gui->w_x), &(gui->w_y));
    gtk_widget_hide(gui->w_profile);
    gtk_widget_show_all(gui->w_chat);
    gtk_window_move(mx_gw(gui->w_chat), gui->w_x, gui->w_y + 22);
}

static t_change_prof change_prof_buf(t_s_glade *gui) {
    t_change_prof change_prof;

    change_prof.login = (char *)gtk_entry_get_text(GTK_ENTRY(gui->e_l_login));
    change_prof.email = (char *)gtk_entry_get_text(GTK_ENTRY(gui->e_p_email));
    change_prof.mobile = (char *)gtk_entry_get_text(GTK_ENTRY(gui->e_p_number));
    change_prof.new_login = (char *)gtk_entry_get_text(GTK_ENTRY(gui->e_p_login));
    change_prof.key= strdup(gui->key);
    return change_prof;
}

static char *create_send_prof(t_change_prof change_prof) {
    char *res = NULL;

    json_object *jobj = json_object_new_object();
    json_object *j_type = json_object_new_string("Change_profile");
    json_object *j_login = json_object_new_string(change_prof.login);
    json_object *j_email = json_object_new_string(change_prof.email);
    json_object *j_number = json_object_new_string(change_prof.mobile);
    json_object *j_new_login = json_object_new_string(change_prof.new_login);
    json_object *j_key = json_object_new_string(change_prof.key);
    json_object_object_add(jobj,"Type", j_type);
    json_object_object_add(jobj,"Login", j_login);
    json_object_object_add(jobj,"Email", j_email);
    json_object_object_add(jobj,"Mobile", j_number);
    json_object_object_add(jobj,"New_login", j_new_login);
    json_object_object_add(jobj,"Security_key", j_key);
    res = (char *)json_object_to_json_string(jobj);
    return res;
}

void mx_change_profile(GtkButton *button, gpointer data) {
    char *send_data = NULL;
    t_s_glade *gui = (t_s_glade *)data;
    t_change_prof change_prof = change_prof_buf(gui);
    int n = 0;
    if (mx_strcmp("", change_prof.login)
        && mx_strcmp("", change_prof.email)
        && mx_strcmp("", change_prof.mobile)) {
            send_data = create_send_prof(change_prof);
            printf("%s\n", send_data);
            n = send(gui->sockfd, send_data, strlen(send_data), 0);
            printf("SEND_DATA = %s\n", send_data);
        }
    (void)button;
    mx_change_window(gui);
}
