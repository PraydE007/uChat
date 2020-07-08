#include "dbase.h"
//A LOT OF LINE
t_datab *mx_create_datab_node(void) {
    t_datab *node = (t_datab*)malloc(sizeof(t_datab));

    if (node) {
        node->logtrigger = 0;
        node->passtrigger = 0;
        node->socket = 0;
        node->id = NULL;
        node->second_id = NULL;
        node->chat_id = NULL;
        node->chat_name = NULL;
        node->email = NULL;
        node->mobile = NULL;
        node->commd = NULL;
        node->type = NULL;
        node->security_key = NULL;
        node->id_db = NULL;
        node->login_db = NULL;
        node->login_db2 = NULL;
        node->email_db = NULL;
        node->mobile_db = NULL;
        node->password_db = NULL;
        node->security_db = NULL;
        node->message_db = NULL;
        node->db = NULL;
        node->j_result = NULL;
    }
    return node;
}
