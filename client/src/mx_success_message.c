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

static const char *json_to_str(json_object *jobj, char *key) {
    const char *value = NULL;

    value = json_object_get_string(json_object_object_get(jobj, key));
    return value;
}

static void display_chat(t_s_glade *gui, const char *sender) {
    mx_push_chat(gui->l_chats, sender);
    gui->if_contact = true;
}

gboolean mx_success_message(void *data) {
    t_s_glade *gui = (t_s_glade *)data;
    json_object *jobj = json_tokener_parse(gui->recv_data);
    const char *message = json_to_str(jobj, "Message");
    const char *sender = json_to_str(jobj, "Sender");
    int count = 0;

    if (!gui->if_contact) {
        if (gui->contacts) {
            while (gui->contacts[count]) {
                if (mx_strcmp(gui->contacts[count], sender)) {
                    display_chat(gui, sender);
                    break;
                }
                count++;
            }
        }
        else
            display_chat(gui, sender);
    }
    if (gui->send_to)
        mx_p_owned(gui->l_messages, message, sender);
    g_timeout_add(10, scroll, gui);
    return 0;
}
