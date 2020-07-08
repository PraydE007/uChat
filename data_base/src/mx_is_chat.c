#include "dbase.h"

static int cb_chat_name_checking(void *datab, int argc, char **argv,
                                                            char **azColName) {
    (void)argc;
    (void)azColName;
    if (datab) {
        t_datab *new_datab = (t_datab *)datab;

        if (!mx_strcmp(new_datab->chat_name, argv[0])) {
            new_datab->passtrigger = 1;
            return 1;
        }
    }
    return 0;
}

bool mx_is_chat(sqlite3 *db, char *sql, t_datab *datab) {
    bool result = false;

    sprintf(sql, "select CHAT_NAME from CHATS;");
    mx_table_setting(db, sql, cb_chat_name_checking, datab);
    if (datab->passtrigger == 1) {
        datab->passtrigger = 0;
        result = true;
    }
    return result;
}
