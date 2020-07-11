#include "client.h"

// gboolean test(void *data) {
//     t_s_glade *gui = (t_s_glade *)data;
//     char *message = (char *)gtk_entry_get_text(GTK_ENTRY(gui->e_message));
//     mx_p_own(gui->l_messages, message);
//     gtk_entry_set_text(GTK_ENTRY(gui->e_message), "");
//     return 0;
// }

static gint scroll(gpointer data) {
    t_s_glade *gui = (t_s_glade *)data;
    GtkScrolledWindow *w = GTK_SCROLLED_WINDOW(gui->s_w_messages);
    GtkAdjustment *ad = gtk_scrolled_window_get_vadjustment(w);
    double l_pos =
        gtk_adjustment_get_upper(ad) + gtk_adjustment_get_page_increment(ad);

    gtk_adjustment_set_value(ad, l_pos);
    return false;
}

void mx_send_message(GtkButton *button, gpointer data) {
    t_s_glade *gui = (t_s_glade *)data;
    int n = 0;
    char *send_data = NULL;
    char *login = (char *)gtk_entry_get_text(GTK_ENTRY(gui->e_l_login));
    char *message = (char *)gtk_entry_get_text(GTK_ENTRY(gui->e_message));

    (void)button;
    if (gui->send_to && mx_strcmp(gui->send_to, "")) {
        json_object *jobj = json_object_new_object();
        json_object *j_type = json_object_new_string("Send_message");
        json_object *j_login = json_object_new_string(login);
        json_object *j_send_to = json_object_new_string(gui->send_to);
        json_object *j_message = json_object_new_string(message);
        json_object *j_key = json_object_new_string(gui->key);
        json_object_object_add(jobj,"Type", j_type);
        json_object_object_add(jobj,"Login", j_login);
        json_object_object_add(jobj,"Chat_name", j_send_to);
        json_object_object_add(jobj,"Message", j_message);
        json_object_object_add(jobj,"Security_key", j_key);

        send_data = (char *)json_object_to_json_string(jobj);

        if (gui->send_to && mx_strcmp(message, "") && mx_strcmp(gui->send_to, "")  && message) {
            n = send(gui->sockfd, send_data, strlen(send_data), 0);
            printf("%s\n", send_data);
            mx_p_own(gui->l_messages, message);
            gtk_entry_set_text(GTK_ENTRY(gui->e_message), "");
            g_timeout_add(10, scroll, gui);
        }
    }
}
