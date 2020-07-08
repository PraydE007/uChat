#include "client.h"

void mx_send_message(GtkButton *button, gpointer data) {
    t_s_glade *gui = (t_s_glade *)data;
    const gchar *message = gtk_entry_get_text(GTK_ENTRY(gui->e_message));
    int n = 0;
    char buffer[2048];
    char *send_data = NULL;

    (void)button;
    json_object *jobj = json_object_new_object();
    json_object *j_type = json_object_new_string("Sending");
//    json_object *j_login = json_object_new_string(gui->e_l_login);                //Нужно придумать как достать логгин
    json_object *j_socket = json_object_new_string(mx_itoa(gui->sockfd));
    json_object_object_add(jobj,"Type", j_type);
//    json_object_object_add(jobj,"Login", j_login);
    json_object_object_add(jobj,"Socket", j_socket);

    send_data = (char *)json_object_to_json_string(jobj);

    n = send(gui->sockfd, send_data, strlen(send_data), 0);
    bzero(buffer, 2048);
    n = recv(gui->sockfd, buffer, 2048, 0);

    mx_push_message(gui->l_messages, message, NULL);

    // SCROLL DOWN
    GtkScrolledWindow *w = GTK_SCROLLED_WINDOW(gui->s_w_messages);
    GtkAdjustment *ad = gtk_scrolled_window_get_vadjustment(w);
    double l_pos = gtk_adjustment_get_upper(ad) + gtk_adjustment_get_page_increment(ad);
    gtk_adjustment_set_value(ad, l_pos);
}
