#include "client.h"

void mx_open_auth_settings(GtkButton *button, gpointer data) {
    GtkWidget *w_settings = (GtkWidget *)data;

    (void)button;
    gtk_widget_show_all(w_settings);
}
