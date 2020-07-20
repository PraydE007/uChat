#include "client.h"

void mx_init_signal_8(t_s_glade *gui) {
    // Emoji window
    g_signal_connect(gui->b_e_close, "clicked",
                    G_CALLBACK(mx_close_window), gui->w_emoji);
}
