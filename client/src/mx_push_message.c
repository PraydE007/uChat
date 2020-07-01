#include "client.h"

void mx_push_message(GtkWidget *lst, const char *msg) {
    GtkWidget *text1 = gtk_label_new(msg);

    gtk_widget_set_hexpand(text1, TRUE);
    gtk_list_box_insert(GTK_LIST_BOX(lst), text1, -1);
    gtk_widget_show_all(lst);
}
