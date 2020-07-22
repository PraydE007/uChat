#include "client.h"

static void mx_change_window(t_s_glade *gui) {
    gtk_window_get_position(mx_gw(gui->w_password), &(gui->w_x), &(gui->w_y));
    // gtk_widget_hide(gui->w_password);
    gtk_widget_show_all(gui->w_password);
    // gtk_widget_hide(gui->b_u_file);
    gtk_window_move(mx_gw(gui->w_password), gui->w_x, gui->w_y + 22);
}

gboolean mx_error_passwd(void *data) {
    t_s_glade *gui = (t_s_glade *) data;
    char *mess = strdup("Wrong password!");
    mx_show_dialog(gui->w_password, mess);
    mx_change_window(gui);
    return 0;
}
