#include "dbase.h"

void mx_dealloc_datab(t_datab **datab) {
    mx_strdel(&((*datab)->id));
    mx_strdel(&((*datab)->second_id));
    mx_strdel(&((*datab)->chat_id));
    mx_strdel(&((*datab)->chat_name));
    mx_strdel(&((*datab)->email));
    mx_strdel(&((*datab)->mobile));
    mx_strdel(&((*datab)->commd));
    mx_strdel(&((*datab)->type));
    mx_strdel(&((*datab)->security_key));
    json_object_put((*datab)->j_result);
    free(*datab);
    (*datab) = NULL;
}
