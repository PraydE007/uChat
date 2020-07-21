#include "dbase.h"
//A LOT OF LINE
t_datab *mx_create_datab_node(void) {
    t_datab *node = (t_datab*)malloc(sizeof(t_datab));

    if (node) {
        node->logtrigger = node->passtrigger = node->socket = node->lenth = 0;
        node->id = node->second_id = node->chat_id = NULL;
        node->chat_name = node->chat_status = node->email = NULL;
        node->mobile = node->commd = node->type = node->security_key = NULL;
        node->id_db = node->login_db = node->login_db2 = NULL;
        node->chat_name_db = NULL;
        node->email_db = node->buffer_db = NULL;
        node->mobile_db = NULL;
        node->password_db = NULL;
        node->security_db = NULL;
        node->message_db = NULL;
        node->fpath_db = NULL;
        node->fsize_db = NULL;
        node->db = NULL;
        node->j_result = NULL;
    }
    return node;
}
