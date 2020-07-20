#include "client.h"

static void init1(t_s_glade *gui) {
    g_signal_connect(gui->b_send, "clicked",
                    G_CALLBACK(mx_send_message), gui);
    g_signal_connect(gui->b_profile, "clicked",
                    G_CALLBACK(mx_open_profile), gui);
    g_signal_connect(gui->b_find, "clicked",
                    G_CALLBACK(mx_find_user), gui);
    g_signal_connect(gui->b_c_settings, "clicked",
                    G_CALLBACK(mx_open_window), gui->w_settings);
    // g_signal_connect(gui->b_emoji, "clicked",
    //                 G_CALLBACK(mx_open_window), gui->w_emoji);
    g_signal_connect(gui->l_chats, "row-activated",
                    G_CALLBACK(mx_open_chat), gui);
    g_signal_connect(gui->b_group, "clicked",
                    G_CALLBACK(mx_open_group), gui);
    g_signal_connect(gui->b_u_file, "clicked",
                    G_CALLBACK(mx_upload_file), gui);
    g_signal_connect(gui->b_r_chat, "clicked",
                    G_CALLBACK(mx_delete_contact), gui);
}

void mx_init_signal_6(t_s_glade *gui) {
    // Chat Window Signals
    init1(gui);
    g_signal_connect(gui->b_u_profile, "clicked",
                    G_CALLBACK(mx_view_profile), gui);
    g_signal_connect(gui->b_edit, "clicked",
                    G_CALLBACK(mx_open_editor), gui);
}
