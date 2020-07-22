#include "client.h"

void mx_anti_resize(GtkWindow *w, GdkEventWindowState *e, gpointer data) {
    (void)data;
    if (e->new_window_state & GDK_WINDOW_STATE_MAXIMIZED) {
        gtk_window_unmaximize(w);
        mx_show_dialog(GTK_WIDGET(w), "Window maximizing is not allowed!");
    }
}
