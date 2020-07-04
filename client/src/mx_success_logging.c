#include "client.h"

gboolean mx_success_logging(void *data) {
    t_s_glade *gui = (t_s_glade *)data;

    mx_logged_in_chat(gui);
    return 0;
}
