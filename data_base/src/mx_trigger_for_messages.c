#include "dbase.h"

void mx_trigger_for_messages(sqlite3 *db, char *sql) {
    sprintf(sql, "CREATE TRIGGER IF NOT EXISTS 'MESSAGE_DELETE' AFTER DELETE " \
    "ON CHATS " \
    "BEGIN " \
    "DELETE FROM 'MESSAGES' WHERE OLD.ID = CHAT_id;" \
    "DELETE FROM 'USERS_CHATS' WHERE OLD.ID = CHAT_id;" \
    "END;");
    mx_table_creation(db, sql, mx_callback);
}
