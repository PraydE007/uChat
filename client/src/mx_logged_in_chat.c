#include "client.h"

void mx_logged_in_chat(t_s_glade *gui) {
    gtk_window_get_position(mx_gw(gui->w_signin), &(gui->w_x), &(gui->w_y));
    gtk_widget_hide(gui->w_signin);
    gtk_widget_hide(gui->w_settings);
    gtk_widget_hide(gui->w_signup);
    gtk_widget_show_all(gui->w_chat);
    gtk_widget_hide(gui->b_c_pad);
    gtk_widget_hide(gui->b_u_file);
    gtk_window_move(mx_gw(gui->w_chat), gui->w_x, gui->w_y + 22);
}
