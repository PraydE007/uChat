#include "client.h"

void mx_close_window(GtkButton *button, gpointer data) {
    GtkWidget *w = (GtkWidget *)data;

    (void)button;
    gtk_widget_hide(w);
}
