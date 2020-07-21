#include "dbase.h"

static void notification_sending(sqlite3 *db, t_datab *datab, char *sql) {
    json_object *receive_message = NULL;
    int lenth = 0;

    lenth = json_object_array_length(datab->j_result);
    for (int i = 0; i < lenth; i++) {
        receive_message = json_object_new_object();
        datab->id_db = mx_js_arr_to_str(datab->j_result, i);
        mx_add_str_to_js(receive_message, "Answer", "The admin has deleted " \
                    "the chat!");
        mx_add_str_to_js(receive_message, "Chat_name",
                                                (char *)datab->chat_name_db);
        mx_js_chts_conts_for_receiver(receive_message, db, datab, sql);
        datab->message_db = json_object_get_string(receive_message);
        sprintf(sql, "select SOCKET from ACTIVITY where USER_id = '%s';",
                                                                datab->id_db);
        mx_table_setting(db, sql, mx_cb_message_sending, datab);
        json_object_put(receive_message );
    }
}

void mx_chat_deleting(sqlite3 *db, t_datab *datab, char *sql) {
    datab->j_result = json_object_new_array();

    sprintf(sql, "select USER_id from USERS_CHATS where CHAT_id = '%s' " \
            "and USER_id != '%s';", datab->chat_id, datab->id);
    mx_table_setting(db, sql, mx_cb_find_user_ids_for_chat, datab->j_result);
    sprintf(sql, "delete from CHATS where ID = %s;", datab->chat_id);
    mx_table_creation(db, sql, mx_callback);
    notification_sending(db, datab, sql);
    json_object_put(datab->j_result);
    datab->j_result = json_object_new_object();
    mx_add_str_to_js(datab->j_result, "Answer", "The admin has deleted " \
                    "the chat!");
    mx_add_str_to_js(datab->j_result, "Chat_name",
                                                (char *)datab->chat_name_db);
}
