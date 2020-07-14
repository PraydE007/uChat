#include "client.h"

static const char *json_to_str(json_object *jobj, char *key) {
    const char *value = NULL;

    value = json_object_get_string(json_object_object_get(jobj, key));
    return value;
}

gboolean mx_success_public_message(void *data) {
    t_s_glade *gui = (t_s_glade *)data;
    json_object *jobj = json_tokener_parse(gui->recv_data);
    const char *message = json_to_str(jobj, "Message");
    // printf("SENT_TO :%s\n", gui->send_to);
    // const char *sender = json_to_str(jobj, "Sender");
    // int count = 0;
    // if (!gui->if_contact) {
    //     if (gui->contacts) {
    //         while (gui->contacts[count]) {
    //             if (mx_strcmp(gui->contacts[count], sender)) {
    //                 mx_push_chat(gui->l_chats, sender);
    //                 gui->if_contact = true;
    //                 break;
    //             }
    //             count++;
    //         }
    //     }
    //     else {
    //         mx_push_chat(gui->l_chats, sender);
    //         gui->if_contact = true;
    //     }
    // }
    if (gui->send_to != NULL) {
        printf("SENT_TO :%s\n", gui->send_to);
        mx_p_owned(gui->l_messages, message);
    }
        // if(mx_strcmp(gui->send_to, ""))
    return 0;
}
