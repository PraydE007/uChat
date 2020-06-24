#include "dbase.h"

void mx_table_messages(char *sql) {
    sprintf(sql, "CREATE TABLE IF NOT EXISTS 'MESSAGES'(" \
            "ID INTEGER PRIMARY KEY AUTOINCREMENT," \
            "SENDER_id INTEGER NOT NULL," \
            "CHAT_id   INTEGER NOT NULL);");
}
