#include "client.h"

void mx_open_profile(GtkButton *button, gpointer data) {
    t_s_glade *gui = (t_s_glade *)data;

    (void)button;
    gtk_window_get_position(mx_gw(gui->w_chat), &(gui->w_x), &(gui->w_y));
    gtk_widget_hide(gui->w_chat);
    gtk_widget_show_all(gui->w_profile);
    gtk_window_move(mx_gw(gui->w_profile), gui->w_x, gui->w_y + 22);
    printf("%s\n", "TEST!!");
}
