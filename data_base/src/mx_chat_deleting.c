#include "dbase.h"

void mx_chat_deleting(sqlite3 *db, t_datab *datab, char *sql) {
    sprintf(sql, "delete from CHATS where ID = %s;", datab->chat_id);
    mx_table_creation(db, sql, mx_callback);
    sprintf(sql, "delete from USERS_CHATS where CHAT_id = %s;",
            datab->chat_id);
    mx_table_creation(db, sql, mx_callback);
    sprintf(sql, "The admin has deleted the chat (%s)!",
            datab->chat_name_db);
    mx_add_str_to_js(datab->j_result, "Answer", sql);
}
