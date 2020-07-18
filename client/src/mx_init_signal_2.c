#include "client.h"

void mx_init_signal_2(t_s_glade *gui) {
    // Uchat Quit Signals
    g_signal_connect(gui->w_signin, "destroy",
                    G_CALLBACK(exit), (void *)0);
    g_signal_connect(gui->w_signup, "destroy",
                    G_CALLBACK(exit), (void *)0);
    g_signal_connect(gui->w_chat, "destroy",
                    G_CALLBACK(exit), (void *)0);
    g_signal_connect(gui->w_profile, "destroy",
                    G_CALLBACK(exit), (void *)0);
    g_signal_connect(gui->w_group, "destroy",
                    G_CALLBACK(exit), (void *)0);
    g_signal_connect(gui->w_edit, "destroy",
                    G_CALLBACK(exit), (void *)0);
}
