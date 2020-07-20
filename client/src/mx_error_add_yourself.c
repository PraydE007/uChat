#include "client.h"

gboolean mx_error_add_yourself(void *data) {
    t_s_glade *gui = (t_s_glade *) data;
    char *mess = strdup("You can not add yourself into contacts!");

    mx_show_dialog(gui->w_chat, mess);
    return 0;
}
