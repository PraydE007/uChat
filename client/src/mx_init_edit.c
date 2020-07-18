#include "client.h"

void mx_init_edit(GtkBuilder **builder, t_s_glade **gui) {
    (*builder) = gtk_builder_new_from_file(MX_WINDOW_EDIT);
    (*gui)->w_edit = mx_get_widget(builder, "window.edit");
    (*gui)->l_l_count = mx_get_widget(builder, "list.lines.count");
    (*gui)->tv_editor = mx_get_widget(builder, "tv.editor");
    (*gui)->b_e_apply = mx_get_widget(builder, "button.apply");
    (*gui)->i_b_e_apply = mx_get_widget(builder, "image.button.apply");
}
