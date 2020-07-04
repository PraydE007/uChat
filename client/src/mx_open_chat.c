#include "client.h"

void mx_open_chat(GtkListBox *box, GtkListBoxRow *row, gpointer data) {
    t_s_glade *gui = (t_s_glade *)data;
    GtkWidget *grid = gtk_bin_get_child(GTK_BIN(row));
    GtkWidget *chat_name = gtk_grid_get_child_at(GTK_GRID(grid), 1, 0);

    (void)box;
    printf("Chat opened for %s\n", gtk_label_get_text(GTK_LABEL(chat_name)));
    mx_clear_container(gui->l_messages);
    gtk_entry_set_text(GTK_ENTRY(gui->e_message), "");
    // gtk_bin_get_child(GTK_BIN(gtk_list_box_get_selected_row(GTK_LIST_BOX(listbox))));
}
