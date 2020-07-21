#include "client.h"

void mx_init_signal_3(t_s_glade *gui) {
    g_signal_connect(gui->b_l_signin, "clicked",
                    G_CALLBACK(mx_logged_in), gui);
    g_signal_connect(gui->b_l_signup, "clicked",
                    G_CALLBACK(mx_open_signup), gui);
    g_signal_connect(gui->b_l_settings, "clicked",
                    G_CALLBACK(mx_open_window), gui->w_settings);
}
