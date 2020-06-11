#include "client.h"

void mx_interface(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    mx_init_auth_screen();
    gtk_main();
}
