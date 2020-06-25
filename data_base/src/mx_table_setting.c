#include "dbase.h"

static int cb_table_set(void *datab, int argc, char **argv, char **azColName) {
    (void)datab;
    (void)argc;
    (void)argv;
    (void)azColName;
    return 0;
}

void mx_table_setting(sqlite3 *db, char *sql) {
    int connection_point;

    connection_point = sqlite3_exec(db, sql, cb_table_set, 0, NULL);
    if (connection_point != SQLITE_OK)
        fprintf(stderr, "error: %s\n", sqlite3_errmsg(db));
}
