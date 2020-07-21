#include "client.h"

static const char *json_to_str(json_object *jobj, char *key) {
    const char *value = NULL;

    value = json_object_get_string(json_object_object_get(jobj, key));
    return value;
}

gboolean mx_success_members_list(void *data) {
    t_s_glade *gui = (t_s_glade *)data;
    json_object *jobj = json_tokener_parse(gui->recv_data);
    const char *members_list = json_to_str(jobj, "Members_list");
    char **splited_list = mx_strsplit(members_list, ',');
    int count = 0;

    mx_clear_container(gui->l_g_group);
    while(splited_list[count]) {
        mx_push_chat(gui->l_g_group, splited_list[count]);
        count++;
    }
    return 0;
}
