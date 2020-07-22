#include "dbase.h"

int mx_cb_find_user_ids_for_chat(void *datab, int argc, char **argv,
                                 char **azColName) {
    (void)argc;
    (void)azColName;
    if (datab) {
        json_object *j_users_id = json_object_new_object();
        json_object *new_datab = (json_object *)datab;
        j_users_id = json_object_new_string(argv[0]);
        mx_add_arr_to_js(new_datab, j_users_id);
    }
    return 0;
}
