#include "dbase.h"

void mx_table_chats(char *sql) {
    sprintf(sql, "CREATE TABLE IF NOT EXISTS 'CHATS'(" \
        "ID INTEGER PRIMARY KEY AUTOINCREMENT);");
}
