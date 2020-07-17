#include "client.h"

void mx_p_owned_img(GtkWidget *lst, const char *filename, const char *name) {
    GtkWidget *align = gtk_label_new("");
    GtkWidget *lol = gtk_label_new(name);
    GtkWidget *grid_box = gtk_grid_new();
    GtkWidget *grid = gtk_grid_new();
    GtkWidget *img = gtk_image_new();

    mx_rep_img_auto(img, filename, 400, 225);
    gtk_widget_set_name(lol, "user_name_label");
    gtk_widget_set_halign(lol, GTK_ALIGN_START);
    gtk_widget_set_valign(lol, GTK_ALIGN_START);
    gtk_widget_set_halign(img, GTK_ALIGN_START);
    gtk_widget_set_hexpand(align, TRUE);
    // GRID INSIDE GRID (BOX)
    gtk_grid_insert_row(GTK_GRID(grid_box), 0);
    gtk_grid_insert_row(GTK_GRID(grid_box), 1);
    gtk_widget_set_hexpand(grid_box, FALSE);
    // GRID INSIDE LIST NODE
    gtk_grid_insert_column(GTK_GRID(grid), 0);
    gtk_grid_insert_column(GTK_GRID(grid), 1);
    // ATTACHING
    gtk_grid_attach(GTK_GRID(grid_box), lol, 0, 0, 1, 2);
    gtk_grid_attach(GTK_GRID(grid_box), img, 0, 1, 1, 2);
    gtk_grid_attach(GTK_GRID(grid), grid_box, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), align, 1, 0, 1, 1);
    gtk_list_box_insert(GTK_LIST_BOX(lst), grid, -1);
    // RENDER
    gtk_widget_show_all(lst);
}
