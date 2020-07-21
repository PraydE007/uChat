#include "dbase.h"

void mx_table_setting(sqlite3 *db, char *sql,
                    int (*callback)(void*, int, char**, char**), void *datab) {
    int connection_point;
    connection_point = sqlite3_exec(db, sql, callback, datab, NULL);
    if (connection_point != SQLITE_OK && connection_point != SQLITE_ABORT)
        fprintf(stderr, "error: %s\n", sqlite3_errmsg(db));
}
