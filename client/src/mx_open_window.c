#include "client.h"

void mx_open_window(GtkButton *button, gpointer data) {
    GtkWidget *w = (GtkWidget *)data;

    (void)button;
    gtk_widget_show_all(w);
}
