#include "client.h"

gint mx_editor_update_lst(gpointer data) {
    t_s_glade *gui = (t_s_glade *)data;
    char num_buf[5] = {0};

    mx_clear_container(gui->l_l_count);
    for (int i = 0; i < 1024; i++) {
        memset(num_buf, 0, 4);
        GtkWidget *num = gtk_label_new(num_buf);
        gtk_list_box_insert(GTK_LIST_BOX(gui->l_l_count), num, -1);
    }
    return 128;
}
