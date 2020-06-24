#include "dbase.h"

t_datab *mx_create_datab_node(void) {
    t_datab *node = (t_datab*)malloc(sizeof(t_datab));


    if (node) {
        node->logtrigger = 0;
        node->passtrigger = 0;
        node->login_db = NULL;
        node->password_db = NULL;
    }
    return node;
}
