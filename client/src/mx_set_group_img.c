#include "client.h"

void mx_set_group_img(GtkButton *button, gpointer data) {
    t_s_glade *gui = (t_s_glade *)data;
    char *group_img = mx_open_file_chooser(GTK_WINDOW(gui->w_group));
    mx_rep_img(gui->i_group, group_img, 250, 250);

    GList *head = gtk_container_get_children(GTK_CONTAINER(gui->l_chats));
    GList *node = head;

    while (node) {
        GtkWidget *grid = gtk_bin_get_child(GTK_BIN(node->data));
        GtkWidget *label = gtk_grid_get_child_at(GTK_GRID(grid), 1, 0);
        GtkWidget *img = gtk_grid_get_child_at(GTK_GRID(grid), 0, 0);
        if (!mx_strcmp(gui->send_to, gtk_label_get_text(GTK_LABEL(label))))
            mx_rep_img(img, group_img, 48, 48);

        node = g_list_next(node);
    }
    g_list_free(head);

    (void)button;
}
