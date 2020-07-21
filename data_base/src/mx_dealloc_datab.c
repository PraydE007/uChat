#include "dbase.h"

void mx_dealloc_datab(t_datab **datab) {
    (*datab)->logtrigger = (*datab)->passtrigger = 0;
    (*datab)->socket = (*datab)->lenth = 0;
    mx_strdel(&((*datab)->id));
    mx_strdel(&((*datab)->second_id));
    mx_strdel(&((*datab)->chat_id));
    mx_strdel(&((*datab)->chat_name));
    mx_strdel(&((*datab)->chat_status));
    mx_strdel(&((*datab)->email));
    mx_strdel(&((*datab)->mobile));
    mx_strdel(&((*datab)->commd));
    mx_strdel(&((*datab)->type));
    mx_strdel(&((*datab)->security_key));
    (*datab)->chat_name_db = (*datab)->email_db = NULL;
    (*datab)->mobile_db = (*datab)->password_db = NULL;
    (*datab)->security_db = (*datab)->buffer_db = NULL;
    (*datab)->message_db = NULL;
    (*datab)->fsize_db = (*datab)->fpath_db = NULL;
    (*datab)->db = NULL;
    (*datab)->j_result = NULL;
    free(*datab);
    (*datab) = NULL;
}
