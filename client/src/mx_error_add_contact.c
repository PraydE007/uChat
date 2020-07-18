#include "client.h"

gboolean mx_error_add_user(void *data) {
    t_s_glade *gui = (t_s_glade *) data;
    char *mess = strdup("You have already this contact in the list!");

    mx_show_dialog(gui->w_chat, mess);
    return 0;
}
