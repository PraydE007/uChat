#include "client.h"

gboolean mx_success_add_contact(void *data) {
    t_s_glade *gui = (t_s_glade *)data;

    char *contact = (char *)gtk_entry_get_text(GTK_ENTRY(gui->e_find));
    if (gui->sender) {
        if(mx_strcmp(gui->sender, contact)) {
            mx_push_chat(gui->l_chats, contact);
            free(gui->sender);
        }
        else {
            mx_show_dialog(gui->w_chat,
            "You have already this contact in the list!");
        }
    }
    else {
        mx_push_chat(gui->l_chats, contact);
    }
    gtk_entry_set_text(GTK_ENTRY(gui->e_find), "");
    return 0;
}
