#include "dbase.h"

static int cb_member_login_checking(void *datab, int argc, char **argv,
                                                            char **azColName) {
    (void)argc;
    (void)azColName;
    if (datab) {
        t_datab *new_datab = (t_datab *)datab;

        if (!mx_strcmp(new_datab->second_id, argv[0])) {
            new_datab->passtrigger = 1;
            return 1;
        }
    }
    return 0;
}

bool mx_is_chat_member(sqlite3 *db, t_datab *datab, char *sql) {
    bool result = false;

    sprintf(sql, "select USER_id from USERS_CHATS where CHAT_id = '%s';",
            datab->chat_id);
    mx_table_setting(db, sql, cb_member_login_checking, datab);
    if (datab->passtrigger == 1) {
        datab->passtrigger = 0;
        result = true;
    }
    return result;
}
