#include "client.h"

void mx_interface(int *argc, char ***argv, int socket) {
    t_s_glade *gui = NULL;

    gtk_init(argc, argv);
    gui = mx_init_auth_screen(socket);
    g_object_unref(gui->icon);
    mx_printstr("gui freeded!\n");
    free(gui);
}
