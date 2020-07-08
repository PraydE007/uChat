#include "client.h"

gboolean mx_success_registr(void *data) {
    t_s_glade *gui = (t_s_glade *)data;

    mx_show_dialog(gui->w_signup, "You have registered successfully!\n");
    gtk_window_get_position(mx_gw(gui->w_signup), &(gui->w_x), &(gui->w_y));
    gtk_widget_hide(gui->w_signup);
    gtk_widget_show_all(gui->w_signin);
    gtk_window_move(mx_gw(gui->w_signin), gui->w_x, gui->w_y + 22);
    return 0;
}
