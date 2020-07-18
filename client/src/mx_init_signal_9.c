#include "client.h"

void mx_init_signal_9(t_s_glade *gui) {
    // Editor window
    g_signal_connect(gui->b_e_apply, "clicked",
                    G_CALLBACK(mx_editor_apply), gui);
}
