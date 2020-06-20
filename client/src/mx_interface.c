#include "client.h"

void mx_interface(int *argc, char ***argv) {
    t_s_glade *gui = NULL;

    gtk_init(argc, argv);
    gui = mx_init_auth_screen();
    mx_printstr("gui freeded!\n");
    free(gui);
}
