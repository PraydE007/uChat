#include "dbase.h"

static int cb_get_chat_contact_list(void *datab, int argc, char **argv,
                                                            char **azColName) {
    (void)argc;
    (void)azColName;
    if (datab) {
        // json_object *j_user = json_object_new_object();
        t_datab *new_datab = (t_datab *)datab;
        char *login = mx_find_user_login(new_datab->db, argv[0]);

        new_datab->commd = mx_strjoin_free_js_value(new_datab->commd, login);
        mx_strdel(&login);
    }
    return 0;
}

void mx_find_chat_contact_list(sqlite3 *db, t_datab *datab, char *sql) {
    datab->db = db;

    sprintf(sql, "select USER_id from USERS_CHATS where CHAT_id = '%s';",
            datab->chat_id);
    mx_table_setting(db, sql, cb_get_chat_contact_list, datab);
    if (datab->commd)
        mx_add_str_to_js(datab->j_result, "Members_list", datab->commd);
// printf("find_chat_contact_list: %s\n", json_object_to_json_string(datab->j_result));//
    mx_strdel(&datab->commd);
}
