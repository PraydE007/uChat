#include "client.h"

void mx_set_group_img(GtkButton *button, gpointer data) {
    t_s_glade *gui = (t_s_glade *)data;
    char *group_img = mx_open_file_chooser(GTK_WINDOW(gui->w_group));
    mx_rep_img(gui->i_group, group_img, 250, 250);
    (void)button;
}
