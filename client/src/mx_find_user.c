#include "client.h"

void mx_find_user(GtkButton *button, gpointer data) {
    t_s_glade *gui = (t_s_glade *)data;
    const gchar *name = gtk_entry_get_text(GTK_ENTRY(gui->e_find));

    (void)button;
    mx_push_chat(gui->l_chats, name);
    gtk_entry_set_text(GTK_ENTRY(gui->e_find), "");
}
