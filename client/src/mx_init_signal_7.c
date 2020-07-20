#include "client.h"

void mx_init_signal_7(t_s_glade *gui) {
    // Group Window Signals
    g_signal_connect(gui->b_g_close, "clicked",
                    G_CALLBACK(mx_close_group), gui);
    g_signal_connect(gui->b_f_user, "clicked",
                    G_CALLBACK(mx_add_user_to_group), gui);
    g_signal_connect(gui->b_g_apply, "clicked",
                    G_CALLBACK(mx_apply_group), gui);
    g_signal_connect(gui->b_b_user, "clicked",
                    G_CALLBACK(mx_delete_user_from_chat), gui);
}
