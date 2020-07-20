#include "client.h"

void mx_init_signal_10(t_s_glade *gui) {
    g_signal_connect(gui->b_p_close, "clicked",
                    G_CALLBACK(mx_close_profile), gui);
    g_signal_connect(gui->b_p_apply, "clicked",
                    G_CALLBACK(mx_change_profile), gui);
    g_signal_connect(gui->b_password, "clicked",
                    G_CALLBACK(mx_open_window), gui->w_password);
    g_signal_connect(gui->b_p_f_image, "clicked",
                    G_CALLBACK(mx_set_profile_img), gui);
}
