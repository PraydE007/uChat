#include "client.h"

static void init1(GtkBuilder **builder, t_s_glade **gui) {
    (*gui)->w_chat = mx_get_widget(builder, "window.chat");
    (*gui)->b_send = mx_get_widget(builder, "button.send");
    (*gui)->i_b_send = mx_get_widget(builder, "image.button.send");
    (*gui)->b_profile = mx_get_widget(builder, "button.profile");
    (*gui)->i_b_profile = mx_get_widget(builder, "image.button.profile");
    (*gui)->b_logout = mx_get_widget(builder, "button.logout");
    (*gui)->i_b_logout = mx_get_widget(builder, "image.button.logout");
    (*gui)->b_c_settings = mx_get_widget(builder, "button.settings");
    (*gui)->i_b_settings = mx_get_widget(builder, "image.button.settings");
    (*gui)->e_message = mx_get_widget(builder, "entry.message");
    (*gui)->e_find = mx_get_widget(builder, "entry.find");
    (*gui)->b_find = mx_get_widget(builder, "button.find");
    (*gui)->i_b_find = mx_get_widget(builder, "image.button.find");
    (*gui)->b_group = mx_get_widget(builder, "button.group");
    (*gui)->i_b_group = mx_get_widget(builder, "image.button.group");
    (*gui)->l_chats = mx_get_widget(builder, "list.chats");
    (*gui)->l_messages = mx_get_widget(builder, "list.messages");
    (*gui)->s_w_messages = mx_get_widget(builder, "s.w.messages");
    (*gui)->w_emoji = mx_get_widget(builder, "window.emoji");
    // (*gui)->b_emoji = mx_get_widget(builder, "button.emoji");
}

void mx_init_chat(GtkBuilder **builder, t_s_glade **gui) {
    (*builder) = gtk_builder_new_from_file(MX_WINDOW_CHAT);
    init1(builder, gui);
    // (*gui)->i_b_emoji = mx_get_widget(builder, "image.button.emoji");
    (*gui)->b_e_close = mx_get_widget(builder, "button.close");
    (*gui)->l_one = mx_get_widget(builder, "label.one");
    (*gui)->b_u_file = mx_get_widget(builder, "button.upload.file");
    (*gui)->i_b_u_file = mx_get_widget(builder, "image.button.upload");
    (*gui)->b_c_pad = mx_get_widget(builder, "box.control.pad");
    (*gui)->b_u_profile = mx_get_widget(builder, "button.user.profile");
    (*gui)->i_b_u_profile = mx_get_widget(builder, "image.button.usr.profile");
    (*gui)->b_r_chat = mx_get_widget(builder, "button.remove.chat");
    (*gui)->i_b_r_chat = mx_get_widget(builder, "image.button.remove.chat");
    (*gui)->b_edit = mx_get_widget(builder, "button.edit");
    (*gui)->i_b_edit = mx_get_widget(builder, "image.button.edit");
    // gtk_label_set_text(GTK_LABEL((*gui)->l_one), get_unicode(0x1F150)); // TRYING UNICODE
}
