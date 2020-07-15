#include "dbase.h"
// CHECK IF WE NEED THIS FUNCTION
static int cb_chat_id_checking(void *datab, int argc, char **argv,
                                                            char **azColName) {
    (void)argc;
    (void)azColName;
    if (datab) {
        t_datab *new_datab = (t_datab *)datab;

        if (!mx_strcmp(new_datab->chat_id, argv[0])) {
            new_datab->passtrigger = 1;
            return 1;
        }
    }
    return 0;
}

bool mx_is_active_chat(sqlite3 *db, t_datab *datab, char *sql) {
    bool result = false;

    sprintf(sql, "select CHAT_id from USERS_CHATS;");
    mx_table_setting(db, sql, cb_chat_id_checking, datab);
    if (datab->passtrigger == 1) {
        datab->passtrigger = 0;
        result = true;
    }
    return result;
}
