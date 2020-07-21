#include "dbase.h"

static void condition_for_chat_delete(sqlite3 *db, t_datab *datab, char *sql) {
    if (mx_is_admin(db, datab, sql)) {
        mx_chat_deleting(db, datab, sql);
    }
    else {
        sprintf(sql, "delete from USERS_CHATS where USER_id = %s " \
                "and CHAT_id = %s;", datab->id, datab->chat_id);
        mx_table_creation(db, sql, mx_callback);
        mx_add_str_to_js(datab->j_result, "Answer", "The chat was deleted!");
    }
}

json_object *mx_if_delete_chat(json_object *jobj, sqlite3 *db, t_datab *datab) {
    datab->j_result = json_object_new_object();
    char sql[255];

    if (mx_is_active(jobj, db, datab)) {
        datab->chat_name_db = mx_js_to_str(jobj, "Chat_name");
        sprintf(sql, "select ID from CHATS where CHAT_NAME = '%s';",
                datab->chat_name_db);
        mx_table_setting(db, sql, mx_cb_find_chat_id, datab);
        condition_for_chat_delete(db, datab, sql);
        mx_js_chts_conts_for_sender(datab->j_result, db, datab, sql);
    }
    else
        mx_add_str_to_js(datab->j_result, "Answer", MX_CHEAT_MESSAGE);
printf("if_delete_chat(j_result): %s\n", json_object_to_json_string(datab->j_result));//
    mx_strdel(&datab->id);// comment in mx_is_active
    mx_strdel(&datab->chat_id);
    return datab->j_result;
}
