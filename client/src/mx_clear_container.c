#include "client.h"

void mx_clear_container(GtkWidget *con) {
    GList *head = gtk_container_get_children(GTK_CONTAINER(con));
    GList *node = head;

    while (node) {
        gtk_widget_destroy(GTK_WIDGET(node->data));
        node = g_list_next(node);
    }
    g_list_free(head);
}
