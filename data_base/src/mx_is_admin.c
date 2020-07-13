#include "dbase.h"

static int cb_chat_status_checking(void *datab, int argc, char **argv,
                                                            char **azColName) {
    (void)argc;
    (void)azColName;
    if (datab) {
        t_datab *new_datab = (t_datab *)datab;

        if (!mx_strcmp("admin", argv[0])) {
            new_datab->passtrigger = 1;
            return 1;
        }
    }
    return 0;
}

bool mx_is_admin(sqlite3 *db, t_datab *datab, char *sql) {
    bool result = false;

    sprintf(sql, "select ID from CHATS where CHAT_NAME = '%s';",
            datab->chat_name_db);
    mx_table_setting(db, sql, mx_cb_find_chat_id, datab);
printf("datab->chat_id: %s\n", datab->chat_id);
    sprintf(sql, "select USER_status from USERS_CHATS where CHAT_id = '%s' " \
            "and USER_id = '%s';", datab->chat_id, datab->id);
    mx_table_setting(db, sql, cb_chat_status_checking, datab);
    if (datab->passtrigger == 1) {
        datab->passtrigger = 0;
        result = true;
    }
    return result;
}
