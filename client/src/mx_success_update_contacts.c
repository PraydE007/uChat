#include "client.h"

static const char *json_to_str(json_object *jobj, char *key) {
    const char *value = NULL;

    value = json_object_get_string(json_object_object_get(jobj, key));
    return value;
}

static void do_loop(t_s_glade *gui, int count) {
    while(gui->contacts[count]) {
        mx_push_chat(gui->l_chats, gui->contacts[count]);
        count++;
    }
}

static void do_second_loop(t_s_glade *gui, int count) {
    while(gui->chats[count]) {
        mx_push_chat(gui->l_chats, gui->chats[count]);
        count++;
    }
}

gboolean mx_success_update_contacts(void *data) {
    t_s_glade *gui = (t_s_glade *)data;
    mx_clear_container(gui->l_chats);
    char *contacts = NULL;
    char *chats = NULL;
    int count = 0;
    json_object *jobj = json_tokener_parse(gui->recv_data);

    contacts = (char *)json_to_str(jobj, "Contacts");
    chats = (char *)json_to_str(jobj, "Chats");
    gui->contacts = mx_strsplit(contacts, ',');
    gui->chats = mx_strsplit(chats, ',');
    if (gui->contacts)
        do_loop(gui, count);
    count = 0;
    if (gui->chats)
        do_second_loop(gui, count);
    mx_clear_container(gui->l_messages);
    if(gui->send_to)
        free(gui->send_to);
    return 0;
}
