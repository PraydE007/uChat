#include "client.h"

static void print_slash(t_s_glade *gui) {
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(gui->tv_term_emul));
    const gchar *message = "\n";
    gtk_text_buffer_insert_at_cursor(buffer, message, 1);
    gtk_text_view_set_buffer(GTK_TEXT_VIEW(gui->tv_term_emul), buffer);
}

void mx_send_message(GtkButton *button, gpointer data) {
    t_s_glade *gui = (t_s_glade *)data;

    (void)button;
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(gui->tv_term_emul));
    const gchar *message = gtk_entry_get_text(GTK_ENTRY(gui->e_message));
    gtk_text_buffer_insert_at_cursor(buffer, message, gtk_entry_get_text_length(GTK_ENTRY(gui->e_message)));
    gtk_text_view_set_buffer(GTK_TEXT_VIEW(gui->tv_term_emul), buffer);
    print_slash(gui);
}
