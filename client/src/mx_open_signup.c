#include "client.h"

void mx_open_signup(GtkButton *button, gpointer data) {
    t_s_glade *gui = (t_s_glade *)data;

    (void)button;
    gtk_window_get_position(mx_gw(gui->w_signin), &(gui->w_x), &(gui->w_y));
    gtk_widget_hide(gui->w_signin);
    gtk_widget_show_all(gui->w_signup);
    gtk_window_move(mx_gw(gui->w_signup), gui->w_x, gui->w_y + 22);

    gtk_entry_set_text(GTK_ENTRY(gui->e_email), "");
    gtk_entry_set_text(GTK_ENTRY(gui->e_r_number), "");
    gtk_entry_set_text(GTK_ENTRY(gui->e_r_login), "");
    gtk_entry_set_text(GTK_ENTRY(gui->e_r_password), "");
    gtk_entry_set_text(GTK_ENTRY(gui->e_r_password2), "");
}
