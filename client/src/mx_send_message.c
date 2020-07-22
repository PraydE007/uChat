#include "client.h"

static gint scroll(gpointer data) {
    t_s_glade *gui = (t_s_glade *)data;
    GtkScrolledWindow *w = GTK_SCROLLED_WINDOW(gui->s_w_messages);
    GtkAdjustment *ad = gtk_scrolled_window_get_vadjustment(w);
    double l_pos =
        gtk_adjustment_get_upper(ad) + gtk_adjustment_get_page_increment(ad);

    gtk_adjustment_set_value(ad, l_pos);
    return false;
}

static void init_json(json_object *jobj, char *login, char *message,
                    t_s_glade *gui) {
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
}

static void display_message(t_s_glade *gui, char *login, char *message) {
    mx_p_own(gui->l_messages, message, login);
    gtk_entry_set_text(GTK_ENTRY(gui->e_message), "");
    g_timeout_add(10, scroll, gui);
}

void mx_send_message(GtkButton *button, gpointer data) {
    t_s_glade *gui = (t_s_glade *)data;
    char *send_data = NULL;
    char *login = (char *)gtk_entry_get_text(GTK_ENTRY(gui->e_l_login));
    char *message = (char *)gtk_entry_get_text(GTK_ENTRY(gui->e_message));
    json_object *jobj = json_object_new_object();

    message = mx_init_filter(message);
    if (mx_strlen(message) > 1024) {
        mx_show_dialog(gui->w_chat, "Message to long!");
        return;
    }
    (void)button;
    if (gui->send_to && mx_strcmp(gui->send_to, "")) {
        message = mx_cat_message(message);
        init_json(jobj, login, message, gui);
        send_data = (char *)json_object_to_json_string(jobj);
        if (gui->send_to && mx_strcmp(message, "")
            && mx_strcmp(gui->send_to, "")  && message) {
            send(gui->sockfd, send_data, strlen(send_data), 0);
            display_message(gui, login, message);
        }
    }
}
