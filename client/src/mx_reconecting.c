#include "client.h"

gboolean mx_reconecting(void *data) {
    t_s_glade *gui = (t_s_glade *) data;
    char *mess = strdup("Lost connection with server, UCHAT will be close for 5 sec.\nPlease try again latter");
    mx_show_dialog(gui->w_chat, mess);
    // gtk_window_get_position(mx_gw(gui->w_chat), &(gui->w_x), &(gui->w_y));
    // gtk_widget_hide(gui->w_chat);
    // gtk_widget_show_all(gui->w_chat);
    // gtk_window_move(mx_gw(gui->w_chat), gui->w_x, gui->w_y + 22);
    return 0;
}
