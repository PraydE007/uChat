#include "client.h"

void mx_init_signup(GtkBuilder **builder, t_s_glade **gui) {
    (*builder) = gtk_builder_new_from_file(MX_WINDOW_SIGNUP);
    (*gui)->w_signup = mx_get_widget(builder, "window.signup");
    (*gui)->b_r_signup = mx_get_widget(builder, "button.signup");
    (*gui)->e_email = mx_get_widget(builder, "entry.email");
    (*gui)->e_r_login = mx_get_widget(builder, "entry.login");
    (*gui)->e_r_password = mx_get_widget(builder, "entry.password");
    (*gui)->e_r_password2 = mx_get_widget(builder, "entry.password2");
    (*gui)->b_r_signin = mx_get_widget(builder, "button.login");
    (*gui)->e_r_mobile = mx_get_widget(builder, "entry.phone");
}
