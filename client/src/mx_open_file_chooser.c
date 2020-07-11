#include "client.h"

char *mx_open_file_chooser(GtkWindow *parent) {
    GtkWidget *dialog = gtk_file_chooser_dialog_new(
        "Choose a file for upload!",
        parent,
        GTK_FILE_CHOOSER_ACTION_OPEN,
        "Open",
        GTK_RESPONSE_ACCEPT,
        NULL
    );
    gint res = gtk_dialog_run(GTK_DIALOG(dialog));
    char *result_str = NULL;

    if (res == GTK_RESPONSE_ACCEPT) {
        GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
        char *filename = gtk_file_chooser_get_filename(chooser);

        result_str = mx_strdup(filename);
        g_free(filename);
    }
    gtk_widget_destroy(dialog);
    return result_str;
}
