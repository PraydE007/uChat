#include "dbase.h"

static int cb_chs_cnts(void *datab, int argc, char **argv,char **colName) {
    char **new_str = (char **)datab;

    (void)argc;
    (void)colName;
    *new_str = mx_strjoin_free_js_value(*new_str, argv[0]);
    return 0;
}

static void call_to_db(json_object *j_result, sqlite3 *db, t_datab *datab,
                                                                char *sql) {
    int connection_point;

    connection_point = sqlite3_exec(db, sql, cb_chs_cnts, &datab->commd, NULL);
    if (connection_point != SQLITE_OK)
        fprintf(stderr, "error: %s\n", sqlite3_errmsg(db));
    if (datab->commd)
        mx_add_str_to_js(j_result, datab->type, datab->commd);
    mx_strdel(&datab->commd);
    mx_strdel(&datab->type);
}

static void js_chts_conts(json_object *j_result, sqlite3 *db, t_datab *datab,
                                                                   char *sql) {
    sprintf(sql, "select CHAT_NAME from CHATS INNER JOIN USERS_CHATS " \
            "ON ID = CHAT_id where CHAT_STATUS = 'public' and USER_id = %s;",
            datab->id_db);
    datab->type = mx_strdup("Chats");
    call_to_db(j_result, db, datab, sql);
    sprintf(sql, "select LOGIN from USERS INNER JOIN CONTACTS " \
            "ON ID = FOLLOWER_id WHERE OWNER_id = %s;", datab->id_db);
    datab->type = mx_strdup("Contacts");
    call_to_db(j_result, db, datab, sql);
}

static void notification_sending(sqlite3 *db, t_datab *datab, char *sql) {
    json_object *receive_message = NULL;
    // datab->j_result = json_object_new_array();
    int lenth = 0;

    lenth = json_object_array_length(datab->j_result);
    for (int i = 0; i < lenth; i++) {
        receive_message = json_object_new_object();
        datab->id_db = mx_js_arr_to_str(datab->j_result, i);
        sprintf(sql, "The admin has deleted the chat (%s)!",
                datab->chat_name_db);
        mx_add_str_to_js(receive_message, "Answer", sql);
        js_chts_conts(receive_message, db, datab, sql);
        datab->message_db = json_object_get_string(receive_message);
printf("datab->message_db: %s\n", datab->message_db);//
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
    mx_table_setting(db, sql, mx_cb_find_user_id_for_chat, datab->j_result);
    sprintf(sql, "delete from CHATS where ID = %s;", datab->chat_id);
    mx_table_creation(db, sql, mx_callback);
    // sprintf(sql, "delete from USERS_CHATS where CHAT_id = %s;",
    //         datab->chat_id);
    // mx_table_creation(db, sql, mx_callback);
    notification_sending(db, datab, sql);
    json_object_put(datab->j_result);
    datab->j_result = json_object_new_object();
    sprintf(sql, "The admin has deleted the chat (%s)!",
            datab->chat_name_db);
    mx_add_str_to_js(datab->j_result, "Answer", sql);
}
