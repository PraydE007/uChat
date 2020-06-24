#include "dbase.h"

void mx_trigger_for_users(sqlite3 *db, char *sql) {
    sprintf(sql, "CREATE TRIGGER IF NOT EXISTS 'USERS_DELETE' AFTER DELETE " \
    "ON USERS " \
    "BEGIN " \
    "DELETE FROM 'USERS_CHATS' WHERE USERS.ID = USERS_CHATS.USER_id);" \
    "END;");
    mx_table_setting(db, sql);
}
