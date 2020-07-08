#include "client.h"

void mx_close_group(GtkButton *btn, gpointer data) {
    t_s_glade *gui = (t_s_glade *)data;

    (void)btn;
    gtk_window_get_position(mx_gw(gui->w_group), &(gui->w_x), &(gui->w_y));
    gtk_widget_hide(gui->w_group);
    gtk_widget_show_all(gui->w_chat);
    gtk_window_move(mx_gw(gui->w_chat), gui->w_x, gui->w_y + 22);
}
