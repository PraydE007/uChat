#include "client.h"

void mx_open_group(GtkButton *btn, gpointer data) {
    t_s_glade *gui = (t_s_glade *)data;
    const gchar *group_name = gtk_entry_get_text(GTK_ENTRY(gui->e_find));

    (void)btn;
    if (mx_strlen((const char *)group_name) > 0) {
        // CREATE GROUP
    }
    else {
        // OPEN GROUP CONTROL FOR SELECTED GROUP
        gtk_window_get_position(mx_gw(gui->w_chat), &(gui->w_x), &(gui->w_y));
        gtk_widget_hide(gui->w_chat);
        gtk_widget_show_all(gui->w_group);
        gtk_window_move(mx_gw(gui->w_group), gui->w_x, gui->w_y + 22);
    }
}
