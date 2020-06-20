#include "client.h"

void mx_logged_in(GtkButton *button, gpointer data) {
    t_s_glade *gui = (t_s_glade *)data;
    const char *login = gtk_entry_get_text(GTK_ENTRY(gui->e_l_login));
    const char *pass = gtk_entry_get_text(GTK_ENTRY(gui->e_l_password));

    (void)button;
    if (!mx_strcmp(login, "admin") && !mx_strcmp(pass, "admin")) {
        gtk_widget_hide(gui->w_signin);
        gtk_widget_hide(gui->w_settings);
        gtk_widget_hide(gui->w_signup);
        mx_logged_in_chat(gui);
    }
}
