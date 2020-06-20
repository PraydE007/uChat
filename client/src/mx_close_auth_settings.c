#include "client.h"

void mx_close_auth_settings(GtkButton *button, gpointer data) {
    GtkWidget *w_settings = (GtkWidget *)data;

    (void)button;
    gtk_widget_hide(w_settings);
}
