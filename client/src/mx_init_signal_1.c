#include "client.h"

void mx_init_signal_1(t_s_glade *gui) {
    g_signal_connect(gui->w_signin, "window-state-event",
                    G_CALLBACK(mx_anti_resize), gui);
    g_signal_connect(gui->w_settings, "window-state-event",
                    G_CALLBACK(mx_anti_resize), gui);
    g_signal_connect(gui->w_signup, "window-state-event",
                    G_CALLBACK(mx_anti_resize), gui);
    g_signal_connect(gui->w_chat, "window-state-event",
                    G_CALLBACK(mx_anti_resize), gui);
    g_signal_connect(gui->w_emoji, "window-state-event",
                    G_CALLBACK(mx_anti_resize), gui);
    g_signal_connect(gui->w_profile, "window-state-event",
                    G_CALLBACK(mx_anti_resize), gui);
    g_signal_connect(gui->w_password, "window-state-event",
                    G_CALLBACK(mx_anti_resize), gui);
    g_signal_connect(gui->w_group, "window-state-event",
                    G_CALLBACK(mx_anti_resize), gui);
    g_signal_connect(gui->w_edit, "window-state-event",
                    G_CALLBACK(mx_anti_resize), gui);
}
