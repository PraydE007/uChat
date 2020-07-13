#include "dbase.h"

void mx_table_users_chats(sqlite3 *db, char *sql) {
    sprintf(sql, "CREATE TABLE IF NOT EXISTS 'USERS_CHATS'(" \
            "USER_id INTEGER NOT NULL," \
            "CHAT_id INTEGER NOT NULL," \
            "USER_status VARCHAR(10));");
    mx_table_creation(db, sql, mx_callback);
}
