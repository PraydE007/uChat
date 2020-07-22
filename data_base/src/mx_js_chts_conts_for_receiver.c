#include "dbase.h"

static int cb_chs_cnts(void *datab, int argc, char **argv,char **colName) {
    char **new_str = (char **)datab;

    (void)argc;
    (void)colName;
    *new_str = mx_strjoin_free_js_value(*new_str, argv[0]);
    return 0;
}

static void call_to_db(json_object *j_result, sqlite3 *db, t_datab *datab,
                       char *sql) {
    int connection_point;

    connection_point = sqlite3_exec(db, sql, cb_chs_cnts, &datab->commd, NULL);
    if (connection_point != SQLITE_OK)
        fprintf(stderr, "error: %s\n", sqlite3_errmsg(db));
    if (datab->commd)
        mx_add_str_to_js(j_result, datab->type, datab->commd);
    mx_strdel(&datab->commd);
    mx_strdel(&datab->type);
}

void mx_js_chts_conts_for_receiver(json_object *j_result, sqlite3 *db,
                                   t_datab *datab, char *sql) {
    sprintf(sql, "select CHAT_NAME from CHATS INNER JOIN USERS_CHATS " \
            "ON ID = CHAT_id where CHAT_STATUS = 'public' and USER_id = %s;",
            datab->id_db);
    datab->type = mx_strdup("Chats");
    call_to_db(j_result, db, datab, sql);
    sprintf(sql, "select LOGIN from USERS INNER JOIN CONTACTS " \
            "ON ID = FOLLOWER_id WHERE OWNER_id = %s;", datab->id_db);
    datab->type = mx_strdup("Contacts");
    call_to_db(j_result, db, datab, sql);
}
