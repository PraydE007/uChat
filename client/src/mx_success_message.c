#include "client.h"

// void find_user(t_s_glade *gui, const char *sender) {
//     printf("%s\n", "TEST");
//     const char *login = gtk_entry_get_text(GTK_ENTRY(gui->e_l_login));
//     char *send_data = NULL;
//     json_object *jobj = json_object_new_object();
//     json_object *j_type = json_object_new_string("Add_contact");
//     json_object *j_login = json_object_new_string(login);
//     json_object *j_passwd = json_object_new_string(sender);
//     json_object *j_key = json_object_new_string(gui->key);
//     json_object_object_add(jobj,"Type", j_type);
//     json_object_object_add(jobj,"Login", j_login);
//     json_object_object_add(jobj,"Contact_login", j_passwd);
//     json_object_object_add(jobj,"Security_key", j_key);

//     send_data = (char *)json_object_to_json_string(jobj);
//     if (mx_strcmp(sender, "")) {
//         printf("SUPER_TEST %s\n", send_data);
//         send(gui->sockfd, send_data, strlen(send_data), 0);
//     }
// }

static const char *json_to_str(json_object *jobj, char *key) {
    const char *value = NULL;

    value = json_object_get_string(json_object_object_get(jobj, key));
    return value;
}

gboolean mx_success_message(void *data) {
    t_s_glade *gui = (t_s_glade *)data;
    json_object *jobj = json_tokener_parse(gui->recv_data);
    const char *message = json_to_str(jobj, "Message");
    const char *sender = json_to_str(jobj, "Sender");
    int count = 0;
    if (!gui->if_contact) {
        if (gui->contacts) {
            while (gui->contacts[count]) {
                if (mx_strcmp(gui->contacts[count], sender)) {
                    mx_push_chat(gui->l_chats, sender);
                    gui->if_contact = true;
                    break;
                }
                count++;
            }
        }
        else {
            mx_push_chat(gui->l_chats, sender);
            gui->if_contact = true;
        }
    }
    if (gui->send_to) {
        if (!mx_strcmp(gui->send_to, json_to_str(jobj, "Sender"))) {
            mx_p_owned(gui->l_messages, message);
        }
    }
    return 0;
}
