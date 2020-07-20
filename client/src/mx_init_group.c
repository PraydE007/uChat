#include "client.h"

void mx_init_group(GtkBuilder **builder, t_s_glade **gui) {
    (*builder) = gtk_builder_new_from_file(MX_WINDOW_GROUP);
    (*gui)->w_group = mx_get_widget(builder, "window.group");
    (*gui)->i_group = mx_get_widget(builder, "image.group.avatar");
    (*gui)->e_group_name = mx_get_widget(builder, "entry.group.name");
    (*gui)->e_g_nickname = mx_get_widget(builder, "entry.nickname");
    (*gui)->b_g_close = mx_get_widget(builder, "button.close");
    (*gui)->b_f_image = mx_get_widget(builder, "button.find.image");
    (*gui)->i_f_image = mx_get_widget(builder, "image.button.find.image");
    (*gui)->b_f_user = mx_get_widget(builder, "button.find.user");
    (*gui)->i_b_f_user = mx_get_widget(builder, "image.button.find.user");
    (*gui)->b_b_user = mx_get_widget(builder, "button.ban.user");
    (*gui)->i_b_user = mx_get_widget(builder, "image.button.ban.user");
    (*gui)->b_g_apply = mx_get_widget(builder, "button.apply");
    (*gui)->l_g_group = mx_get_widget(builder, "list.group.users");
}
