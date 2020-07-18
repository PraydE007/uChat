#include "client.h"
static const char *json_to_str(json_object *jobj, char *key) {
    const char *value = NULL;

    value = json_object_get_string(json_object_object_get(jobj, key));
    return value;
}

static void fill_profile(t_s_glade *gui) {
    json_object *jobj = json_tokener_parse(gui->recv_data);
    char *login = (char *)json_to_str(jobj, "Login");
    char *email = (char *)json_to_str(jobj, "Email");
    char *mobile = (char *)json_to_str(jobj, "Mobile");

    gtk_entry_set_text(GTK_ENTRY(gui->e_p_login), login);
    gtk_entry_set_text(GTK_ENTRY(gui->e_p_email), email);
    gtk_entry_set_text(GTK_ENTRY(gui->e_p_number), mobile);

}

static void change_window(t_s_glade *gui) {
    gtk_window_get_position(mx_gw(gui->w_chat), &(gui->w_x), &(gui->w_y));
    gtk_editable_set_editable(GTK_EDITABLE(gui->e_p_login), FALSE);
    gtk_editable_set_editable(GTK_EDITABLE(gui->e_p_email), FALSE);
    gtk_editable_set_editable(GTK_EDITABLE(gui->e_p_number), FALSE);
    gtk_widget_show_all(gui->w_profile);
    gtk_widget_hide(gui->w_chat);
    gtk_widget_hide(gui->b_password);
    gtk_widget_hide(gui->b_p_apply);
    gtk_window_move(mx_gw(gui->w_profile), gui->w_x, gui->w_y + 22);
    gtk_widget_hide(gui->b_p_f_image);
}
gboolean mx_success_profile_info(void *data) {
    t_s_glade *gui = (t_s_glade *)data;
    fill_profile(gui);
    change_window(gui);
    return 0;
}
