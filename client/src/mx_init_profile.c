#include "client.h"

void mx_init_profile(GtkBuilder **builder, t_s_glade **gui) {
    (*builder) = gtk_builder_new_from_file(MX_WINDOW_PROFILE);
    (*gui)->w_profile = mx_get_widget(builder, "window.profile");
    (*gui)->i_avatar = mx_get_widget(builder, "image.avatar");
    (*gui)->e_p_login = mx_get_widget(builder, "entry.login");
    (*gui)->e_p_email = mx_get_widget(builder, "entry.email");
    (*gui)->e_p_number = mx_get_widget(builder, "entry.number");
    (*gui)->b_password = mx_get_widget(builder, "button.password");
    (*gui)->b_p_apply = mx_get_widget(builder, "button.apply");
    (*gui)->b_p_close = mx_get_widget(builder, "button.close");
    (*gui)->w_password = mx_get_widget(builder, "window.password");
    (*gui)->e_p_oldpass = mx_get_widget(builder, "entry.oldpass");
    (*gui)->e_p_newpass1 = mx_get_widget(builder, "entry.newpass1");
    (*gui)->e_p_newpass2 = mx_get_widget(builder, "entry.newpass2");
    (*gui)->b_pp_apply = mx_get_widget(builder, "button.password.apply");
    (*gui)->b_pp_close = mx_get_widget(builder, "button.password.close");
    (*gui)->b_p_f_image = mx_get_widget(builder, "button.find.image");
    (*gui)->i_p_f_image = mx_get_widget(builder, "image.button.find.image");
}
