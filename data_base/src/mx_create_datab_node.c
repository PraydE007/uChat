#include "dbase.h"

t_datab *mx_create_datab_node(void) {
    t_datab *node = (t_datab*)malloc(sizeof(t_datab));


    if (node) {
        node->id = 0;
        node->logtrigger = 0;
        node->passtrigger = 0;
        node->socket = 0;
        node->id = NULL;
        node->second_id = NULL;
        node->commd = NULL;
        node->type = NULL;
        node->login_db = NULL;
        node->login_db2 = NULL;
        node->password_db = NULL;
    }
    return node;
}
