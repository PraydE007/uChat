#include "dbase.h"

void mx_table_chats(char *sql) {
    sprintf(sql, "CREATE TABLE IF NOT EXISTS 'CHATS'(" \
            "ID INTEGER PRIMARY KEY AUTOINCREMENT," \
            "CHAT_NAME   VARCHAR(50) NOT NULL," \
            "CHAT_STATUS VARCHAR(50) NOT NULL);");
}
