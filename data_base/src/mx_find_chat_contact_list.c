#include "dbase.h"

static int cb_get_chat_contact_list(void *datab, int argc, char **argv,
                                                            char **azColName) {
    (void)argc;
    (void)azColName;
    if (datab) {
        json_object *j_user = json_object_new_object();
        t_datab *new_datab = (t_datab *)datab;
        char *login = mx_find_user_login(new_datab->db, argv[0]);

        mx_add_str_to_js(j_user, "Login", login);
        mx_add_arr_to_js(new_datab->j_result, j_user);
        mx_strdel(&login);
    }
    return 0;
}

void mx_find_chat_contact_list(sqlite3 *db, t_datab *datab, char *sql) {
    sprintf(sql, "select USER_id from USERS_CHATS where CHAT_id = '%s';",
            datab->chat_id);
    mx_table_setting(db, sql, cb_get_chat_contact_list, datab);

printf("find_chat_contact_list: %s\n", json_object_to_json_string(datab->j_result));//
}
