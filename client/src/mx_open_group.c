#include "client.h"

void mx_open_group(GtkButton *btn, gpointer data) {
    t_s_glade *gui = (t_s_glade *)data;
    const gchar group_name = gtk_entry_get_text(GTL_ENTRY(gui->e_find));

    (void)btn;
    if (mx_strlen(group_name) > 0) {
        // CREATE GROUP
    }
    else {
        // OPEN GROUP CONTROL FOR SELECTED GROUP
    }
}
