#include "client.h"

void mx_open_editor(GtkButton *button, gpointer data) {
    t_s_glade *gui = (t_s_glade *)data;
    const gchar *text = gtk_entry_get_text(GTK_ENTRY(gui->e_message));
    GtkTextBuffer *b = gtk_text_view_get_buffer(GTK_TEXT_VIEW(gui->tv_editor));

    gtk_text_buffer_set_text(b, text, -1);
    gtk_text_view_set_buffer(GTK_TEXT_VIEW(gui->tv_editor), b);
    gui->tag = mx_editor_update_lst(gui);
    // gui->tag = g_timeout_add(1000, mx_editor_update_lst, gui);
    (void)button;
    gtk_window_get_position(mx_gw(gui->w_chat), &(gui->w_x), &(gui->w_y));
    gtk_widget_hide(gui->w_chat);
    gtk_widget_show_all(gui->w_edit);
    gtk_window_move(mx_gw(gui->w_edit), gui->w_x, gui->w_y + 22);
}
