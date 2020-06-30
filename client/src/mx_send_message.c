#include "client.h"

void mx_send_message(GtkButton *button, gpointer data) {
    t_s_glade *gui = (t_s_glade *)data;
    const gchar *message = gtk_entry_get_text(GTK_ENTRY(gui->e_message));

    (void)button;
    mx_push_message(gui->l_messages, message);
}
