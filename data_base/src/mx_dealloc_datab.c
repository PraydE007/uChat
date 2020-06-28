#include "dbase.h"

void mx_dealloc_datab(t_datab **datab) {
    mx_strdel(&((*datab)->id));
    mx_strdel(&((*datab)->second_id));
    mx_strdel(&((*datab)->commd));
    mx_strdel(&((*datab)->type));
    free(*datab);
    (*datab) = NULL;
}
