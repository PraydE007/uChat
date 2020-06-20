#include "dbase.h"

void mx_table_users(char *sql) {
    sprintf(sql, "CREATE TABLE IF NOT EXISTS 'USERS'(" \
        "ID INTEGER PRIMARY KEY AUTOINCREMENT," \
        "LOGIN          VARCHAR(50)     NOT NULL," \
        "PASSWORD       VARCHAR(50)     NOT NULL," \
        "EMAIL          VARCHAR(50)     NOT NULL);");
}
