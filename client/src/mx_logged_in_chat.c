#include "client.h"

void mx_logged_in_chat(t_s_glade *gui) {
    gtk_widget_hide(gui->w_signin);
    gtk_widget_hide(gui->w_settings);
    gtk_widget_hide(gui->w_signup);
    gtk_widget_show_all(gui->w_chat);
}
