#include "client.h"

gboolean mx_error_find_user(void *data) {
    t_s_glade *gui = (t_s_glade *) data;
    char *mess = strdup("There is no such user in the uchat!");

    mx_show_dialog(gui->w_chat, mess);
    return 0;
}
