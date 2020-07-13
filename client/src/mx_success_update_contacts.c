#include "client.h"

gboolean mx_success_update_contacts(void *data) {
    t_s_glade *gui = (t_s_glade *)data;
    mx_clear_container(gui->l_chats);

    return 0;
}
