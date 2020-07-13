#include "client.h"

gboolean mx_error_logging(void *data) {
    t_s_glade *gui = (t_s_glade *) data;

    mx_show_dialog(gui->w_signin, "Login or password is incorrect!");
    return 0;
}
