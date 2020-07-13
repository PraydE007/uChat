#include "client.h"

gboolean mx_error_create_chat(void *data) {
    t_s_glade *gui = (t_s_glade *) data;
    char *mess = strdup("A chat or an user with such name already exists!");

    mx_show_dialog(gui->w_chat, mess);
    return 0;
}
