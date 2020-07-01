#include "dbase.h"

void mx_table_contacts(sqlite3 *db, char *sql) {
    sprintf(sql, "CREATE TABLE IF NOT EXISTS 'CONTACTS'(" \
            "OWNER_id    INTEGER NOT NULL," \
            "FOLLOWER_id INTEGER NOT NULL);");
    mx_table_creation(db, sql, mx_callback);
}
