#include "client.h"

gboolean mx_reconecting(void *data) {
    t_s_glade *gui = (t_s_glade *) data;
    char *mess = strdup("Lost connection with server, UCHAT will be close for 3 sec.\nPlease try again latter");
        mx_show_dialog(gui->w_chat, mess);
    return 0;
}
