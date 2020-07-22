#include "dbase.h"

void mx_trigger_for_activity(sqlite3 *db, char *sql) {
    sprintf(sql, "CREATE TRIGGER IF NOT EXISTS 'ACTIVITY_INS' AFTER UPDATE " \
            "ON USERS " \
            "BEGIN " \
            "INSERT INTO 'ACTIVITY'(USER_id, SOCKET, SECURITY_KEY) " \
            "VALUES (NEW.ID, NEW.SOCKET, NEW.SECURITY_KEY);" \
            "END;");
    mx_table_creation(db, sql, mx_callback);
}
