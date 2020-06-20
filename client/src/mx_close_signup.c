#include "client.h"

void mx_close_signup(GtkButton *button, gpointer data) {
    t_s_glade *gui = (t_s_glade *)data;

    (void)button;
    gtk_widget_hide(gui->w_signup);
    gtk_widget_show_all(gui->w_signin);
}
