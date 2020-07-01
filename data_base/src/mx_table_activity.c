#include "dbase.h"

void mx_table_activity(sqlite3 *db, char *sql) {
    sprintf(sql, "CREATE TABLE IF NOT EXISTS 'ACTIVITY'(" \
        "USER_id    INTEGER NOT NULL," \
        "SOCKET         INTEGER," \
        "SECURITY_KEY   CHAR);");
    mx_table_creation(db, sql, mx_callback);
}
