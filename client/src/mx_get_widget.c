#include "client.h"

GtkWidget *mx_get_widget(GtkBuilder **b, char *id) {
    GtkWidget *x = GTK_WIDGET(gtk_builder_get_object(*b, id));

    return x;
}
