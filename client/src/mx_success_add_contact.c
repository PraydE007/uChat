#include "client.h"

gboolean mx_success_add_contact(void *data) {
    t_s_glade *gui = (t_s_glade *)data;

    char *contact = (char *)gtk_entry_get_text(GTK_ENTRY(gui->e_find));
    mx_push_chat(gui->l_chats, contact);
    gtk_entry_set_text(GTK_ENTRY(gui->e_find), "");
    return 0;
}
