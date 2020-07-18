#include "client.h"

void mx_init_signal_11(t_s_glade *gui) {
    // Password Window Signals
    g_signal_connect(gui->b_pp_close, "clicked",
                    G_CALLBACK(mx_close_window), gui->w_password);
    g_signal_connect(gui->b_pp_apply, "clicked",
                     G_CALLBACK(mx_change_pass), gui);
    g_signal_connect(gui->b_logout, "clicked",
                     G_CALLBACK(mx_logout), gui);
    g_signal_connect(gui->b_f_image, "clicked",
                     G_CALLBACK(mx_set_group_img), gui);
}
