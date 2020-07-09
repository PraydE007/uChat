#include "client.h"

void mx_upload_file(GtkButton *btn, gpointer data) {
    t_s_glade *gui = (t_s_glade *)data;
    char *filepath = mx_open_file_chooser(GTK_WINDOW(gui->w_chat));

    (void)btn;
    (void)filepath;
    // gtk_widget_show_all(gui->f_chooser);
}
