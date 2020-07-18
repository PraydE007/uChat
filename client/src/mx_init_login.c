#include "client.h"

void mx_init_login(GtkBuilder **builder, t_s_glade **gui) {
    (*builder) = gtk_builder_new_from_file(MX_WINDOW_LOGIN);
    (*gui)->w_signin = mx_get_widget(builder, "window.login");
    (*gui)->e_l_login = mx_get_widget(builder, "entry.login");
    (*gui)->e_l_password = mx_get_widget(builder, "entry.password");
    (*gui)->b_l_signin = mx_get_widget(builder, "button.signin");
    (*gui)->b_l_signup = mx_get_widget(builder, "button.signup");
    (*gui)->b_l_settings = mx_get_widget(builder, "button.settings");
    (*gui)->w_settings = mx_get_widget(builder, "window.settings");
    (*gui)->b_s_close = mx_get_widget(builder, "button.close");
    (*gui)->b_t_light = mx_get_widget(builder, "button.theme.light");
    (*gui)->b_t_dark = mx_get_widget(builder, "button.theme.dark");
    (*gui)->b_t_custom = mx_get_widget(builder, "button.theme.custom");
    (*gui)->b_t_connect = mx_get_widget(builder, "button.theme.connect");
}
