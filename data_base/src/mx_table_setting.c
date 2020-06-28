#include "dbase.h"

void mx_table_setting(sqlite3 *db, char *sql) {
    int connection_point;

    connection_point = sqlite3_exec(db, sql, mx_callback, 0, NULL);
    if (connection_point != SQLITE_OK)
        fprintf(stderr, "error: %s\n", sqlite3_errmsg(db));
}
