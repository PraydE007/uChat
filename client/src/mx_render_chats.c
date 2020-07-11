#include "client.h"

static const char *json_to_str(json_object *jobj, char *key) {
    const char *value = NULL;

    value = json_object_get_string(json_object_object_get(jobj, key));
    return value;
}

gboolean mx_render_chats(t_s_glade *gui) {
    json_object *jobj = json_tokener_parse(gui->recv_data);
    char **get_splited_chats = NULL;
    char *get_all_chats = (char *)json_to_str(jobj, "Chats");

    if (get_all_chats) {
        get_splited_chats = mx_strsplit(get_all_chats, ',');
        for (int i = 0; get_splited_chats[i]; i++)
            mx_push_chat(gui->l_chats, get_splited_chats[i]);
            gtk_entry_set_text(GTK_ENTRY(gui->e_find), "");
    }
    return 0;
}
