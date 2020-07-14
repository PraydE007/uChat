#include "dbase.h"

void mx_find_chat_name(sqlite3 *db, t_datab *datab, char *sql) {
    if (!mx_is_chat(db, sql, datab)) {
        datab->logtrigger = 1;
        datab->chat_name = mx_strjoin_free(datab->chat_name, datab->login_db);
        if (!mx_is_chat(db, sql, datab)) {
            mx_strdel(&datab->chat_name);
            datab->chat_name = mx_strjoin(datab->login_db, datab->login_db2);
        }
    }
}
