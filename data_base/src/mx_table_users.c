#include "dbase.h"

void mx_table_users(sqlite3 *db, char *sql) {
    sprintf(sql, "CREATE TABLE IF NOT EXISTS 'USERS'(" \
        "ID INTEGER PRIMARY KEY AUTOINCREMENT," \
        "LOGIN          VARCHAR(50)     NOT NULL," \
        "PASSWORD       VARCHAR(50)     NOT NULL," \
        "EMAIL          VARCHAR(50)     NOT NULL," \
        "MOBILE         VARCHAR(20)     NOT NULL," \
        "SOCKET         INTEGER," \
        "SECURITY_KEY   CHAR);");
    mx_table_creation(db, sql, mx_callback);
}
