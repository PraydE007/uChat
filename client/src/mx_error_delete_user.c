#include "client.h"

gboolean mx_error_delete_user(void *data) {
    t_s_glade *gui = (t_s_glade *) data;
    char *mess = strdup("You can not delete users from this chat!");

    mx_show_dialog(gui->w_group, mess);
    return 0;
}
