#include "client.h"

void mx_logout(GtkButton *button, gpointer data) {
    t_s_glade *gui = (t_s_glade *)data;
    // printf("%s\n", "TEST");
    gtk_widget_hide(gui->w_chat);
    mx_clear_container(gui->l_chats);
    gtk_widget_show_all(gui->w_signin);
    (void)button;
}
