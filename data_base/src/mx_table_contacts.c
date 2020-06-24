#include "dbase.h"

void mx_table_contacts(char *sql) {
    sprintf(sql, "CREATE TABLE IF NOT EXISTS 'CONTACTS'(" \
            "OWNER_id    INTEGER NOT NULL," \
            "FOLLOWER_id INTEGER NOT NULL);");
}
