#include "dbase.h"

void mx_data_base_creation(sqlite3 **db) {
    int connection_point;
    char sql[512];

    connection_point = sqlite3_open("chat_base.db", db);
    if(connection_point)
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(*db));
    else
        fprintf(stdout, "Opened database successfully\n");
    sprintf(sql, "DROP TABLE IF EXISTS ACTIVITY;");
    mx_table_creation(*db, sql, mx_callback);
    mx_table_users(*db, sql);
    mx_table_chats(*db, sql);
    mx_table_users_chats(*db, sql);
    mx_table_messages(*db, sql);
    mx_table_contacts(*db, sql);
    mx_table_activity(*db, sql);
    mx_trigger_for_activity(*db, sql);
    mx_trigger_for_users(*db, sql);
    mx_trigger_for_messages_delete(*db, sql);
}
