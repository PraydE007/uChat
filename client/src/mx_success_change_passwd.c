#include "client.h"

gboolean mx_success_change_passwd(void *data) {
    t_s_glade *gui = (t_s_glade *)data;
        mx_show_dialog(gui->w_profile, "Password changed!\n");
        gtk_window_get_position(mx_gw(gui->w_profile), &(gui->w_x), &(gui->w_y));
        gtk_widget_hide(gui->w_password);
        gtk_widget_show_all(gui->w_profile);
        gtk_window_move(mx_gw(gui->w_profile), gui->w_x, gui->w_y + 22);
    return 0;
}
