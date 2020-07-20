#include "client.h"

void mx_init_signal_5(t_s_glade *gui) {
    g_signal_connect(gui->b_r_signin, "clicked",
                    G_CALLBACK(mx_close_signup), gui);
    g_signal_connect(gui->b_r_signup, "clicked",
                    G_CALLBACK(mx_registration), gui);
}
