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

static t_buf_suc_mess suc_message(json_object *jobj) {
    t_buf_suc_mess suc_mess;

    suc_mess.message = json_to_str(jobj, "Message");
    suc_mess.sender = json_to_str(jobj, "Sender");
    suc_mess.contacts = (char *)json_to_str(jobj, "Contacts");
    suc_mess.sp_cont = mx_strsplit(suc_mess.contacts, ',');

    return suc_mess;
}

gboolean mx_success_message(void *data) {
    t_s_glade *gui = (t_s_glade *)data;
    json_object *jobj = json_tokener_parse(gui->recv_data);
    t_buf_suc_mess suc_mess = suc_message(jobj);
    int count = 0;

    gui->sender = mx_strdup(suc_mess.sender);
    if (!gui->if_contact) {
        if (suc_mess.sp_cont) {
            while (suc_mess.sp_cont[count]) {
                if (mx_strcmp(suc_mess.sp_cont[count], suc_mess.sender)) {
                    display_chat(gui, suc_mess.sender);
                    break;
                }
                count++;
            }
        }
        else
            display_chat(gui, suc_mess.sender);
    }
    if (gui->send_to)
        if (!mx_strcmp(gui->send_to, suc_mess.sender))
            mx_p_owned(gui->l_messages, suc_mess.message, suc_mess.sender);
    g_timeout_add(10, scroll, gui);
    return 0;
}
