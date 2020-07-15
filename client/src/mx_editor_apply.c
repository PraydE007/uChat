#include "client.h"

void mx_editor_apply(GtkButton *button, gpointer data) {
    t_s_glade *gui = (t_s_glade *)data;
    GtkTextIter start;
    GtkTextIter end;
    GtkTextBuffer *b = gtk_text_view_get_buffer(GTK_TEXT_VIEW(gui->tv_editor));
    const gchar *text;

    gtk_text_buffer_get_bounds(b, &start, &end);
    text = gtk_text_buffer_get_text(b, &start, &end, FALSE);
    gtk_entry_set_text(GTK_ENTRY(gui->e_message), text);
    // g_source_remove(gui->tag);
    (void)button;
    gtk_window_get_position(mx_gw(gui->w_edit), &(gui->w_x), &(gui->w_y));
    gtk_widget_hide(gui->w_edit);
    gtk_widget_show_all(gui->w_chat);
    gtk_window_move(mx_gw(gui->w_chat), gui->w_x, gui->w_y + 22);
}
