#include "client.h"

void mx_set_profile_img(GtkButton *button, gpointer data) {
    t_s_glade *gui = (t_s_glade *)data;
    char *group_img = mx_open_file_chooser(GTK_WINDOW(gui->w_profile));
    char *login = (char *)gtk_entry_get_text(GTK_ENTRY(gui->e_l_login));
    mx_rep_img(gui->i_avatar, group_img, 225, 225);

    GList *head = gtk_container_get_children(GTK_CONTAINER(gui->l_chats));
    GList *node = head;

    while (node) {
        GtkWidget *grid = gtk_bin_get_child(GTK_BIN(node->data));
        GtkWidget *label = gtk_grid_get_child_at(GTK_GRID(grid), 1, 0);
        GtkWidget *img = gtk_grid_get_child_at(GTK_GRID(grid), 0, 0);
        if (!mx_strcmp(login, gtk_label_get_text(GTK_LABEL(label))))
            mx_rep_img(img, group_img, 48, 48);

        node = g_list_next(node);
    }
    g_list_free(head);
    (void)button;
}
