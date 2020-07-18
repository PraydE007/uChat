#include "dbase.h"

void mx_table_messages(sqlite3 *db, char *sql) {
    sprintf(sql, "CREATE TABLE IF NOT EXISTS 'MESSAGES'(" \
            "ID INTEGER PRIMARY KEY AUTOINCREMENT," \
            "SENDER_id    INTEGER NOT NULL," \
            "CHAT_id      INTEGER NOT NULL," \
            "MESSAGE_text TEXT    NOT NULL," \
            "IS_file      VARCHAR(50)," \
            "FILE_size    INTEGER);");
    mx_table_creation(db, sql, mx_callback);
}
