#include "client.h"

void mx_show_dialog(GtkWidget *parent, char *message) {
    GtkDialogFlags flags = GTK_DIALOG_DESTROY_WITH_PARENT;
    GtkWidget *dialog = gtk_message_dialog_new(
        GTK_WINDOW(parent),
        flags,
        GTK_MESSAGE_WARNING,
        GTK_BUTTONS_OK,
        "\n%s",
        message
    );

    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}
