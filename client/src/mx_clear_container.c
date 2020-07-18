#include "client.h"

void mx_clear_container(GtkWidget *con) {
    GList *head = gtk_container_get_children(GTK_CONTAINER(con));
    GList *node = head;

    while (node) {
        // GtkWidget *grid = gtk_bin_get_child(GTK_BIN(node->data));
        // GtkWidget *label = gtk_grid_get_child_at(GTK_GRID(grid), 1, 0);
        gtk_widget_destroy(GTK_WIDGET(node->data));
        node = g_list_next(node);
    }
    g_list_free(head);
}
