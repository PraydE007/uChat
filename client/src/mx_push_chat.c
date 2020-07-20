#include "client.h"

void mx_push_chat(GtkWidget *lst, const char *user_name) {
    int len = mx_strlen(user_name);

    if (len > 0 && len <= 24) {
        GtkWidget *grid1 = gtk_grid_new();
        GtkWidget *image1 = mx_load_img(MX_AVATAR_MIS, 48, 48);
        GtkWidget *text1 = gtk_label_new(user_name);
        gtk_widget_set_hexpand(text1, TRUE);
        gtk_grid_insert_column(GTK_GRID(grid1), 0);
        gtk_grid_insert_column(GTK_GRID(grid1), 1);
        gtk_grid_attach(GTK_GRID(grid1), image1, 0, 0, 1, 1);
        gtk_grid_attach(GTK_GRID(grid1), text1, 1, 0, 1, 1);
        gtk_list_box_insert(GTK_LIST_BOX(lst), grid1, -1);
        gtk_widget_show_all(lst);
    }
}
