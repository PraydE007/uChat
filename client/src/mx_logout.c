#include "client.h"

void mx_logout(GtkButton *button, gpointer data) {
    t_s_glade *gui = (t_s_glade *)data;
    // printf("%s\n", "TEST");
    gtk_window_get_position(mx_gw(gui->w_chat), &(gui->w_x), &(gui->w_y));
    gtk_widget_hide(gui->w_chat);
    gtk_widget_show_all(gui->w_signin);
    gtk_window_move(mx_gw(gui->w_signin), gui->w_x, gui->w_y + 22);
    mx_clear_container(gui->l_chats);
    (void)button;
}
