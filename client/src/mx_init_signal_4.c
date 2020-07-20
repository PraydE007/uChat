#include "client.h"

void mx_init_signal_4(t_s_glade *gui) {
    g_signal_connect(gui->b_s_close, "clicked",
                    G_CALLBACK(mx_close_window), gui->w_settings);
    g_signal_connect(gui->b_t_light, "clicked",
                    G_CALLBACK(mx_light_theme), gui);
    g_signal_connect(gui->b_t_dark, "clicked",
                    G_CALLBACK(mx_dark_theme), gui);
}
