#include "dbase.h"

static int cb_users_id_for_chat(void *datab, int argc, char **argv,
                                                            char **azColName) {
    (void)argc;
    (void)azColName;
    if (datab) {
        json_object *j_users_id = json_object_new_object();
        json_object *new_datab = (json_object *)datab;
        j_users_id = json_object_new_string(argv[0]);
        mx_add_arr_to_js(new_datab, j_users_id);
    }
    return 0;
}

static void insert_message(char *sql, sqlite3 *db, t_datab *datab) {
    sprintf(sql, "insert into MESSAGES (SENDER_id, CHAT_id, MESSAGE_text)" \
            "values('%s', '%s', '%s')", datab->id, datab->chat_id,
            datab->message_db);
    mx_table_creation(db, sql, mx_callback);
}

static int message_sending(void *datab, int argc, char **argv,
                                                            char **azColName) {
    (void)argc;
    (void)azColName;
    if (datab) {
printf("argv[0]: %s\n", argv[0]); //
        t_datab *new_datab = (t_datab *)datab;
        int n;
        json_object *receive_message = json_object_new_object();
        mx_add_str_to_js(receive_message, "Answer", "Receive_message");
        mx_add_str_to_js(receive_message, "Sender", (char *)new_datab->login_db);
        mx_add_str_to_js(receive_message, "Message", (char *)new_datab->message_db);
        new_datab->message_db = json_object_get_string(receive_message);
printf("new_datab->message_db: %d\n", mx_strlen(new_datab->message_db)); //
        n = send(mx_atoi(argv[0]), new_datab->message_db, mx_strlen(new_datab->message_db),  0);

    }
    return 0;
}

static void db_handler_for_message(sqlite3 *db, t_datab *datab, char *sql) {
    int lenth = 0;

    sprintf(sql, "select ID from CHATS where CHAT_NAME = '%s';",
            datab->chat_name);
    mx_table_setting(db, sql, mx_cb_chat_id_finder, datab);
    insert_message(sql, db, datab);
    sprintf(sql, "select USER_id from USERS_CHATS where CHAT_id = '%s' " \
            "AND USER_id != '%s';", datab->chat_id, datab->id);
    mx_table_setting(db, sql, cb_users_id_for_chat, datab->j_result);
    lenth = json_object_array_length(datab->j_result);;
    for (int i = 0; i < lenth; i++) {
        datab->id_db = json_object_get_string(
                                json_object_array_get_idx(datab->j_result, i));
        sprintf(sql, "select SOCKET from ACTIVITY where USER_id = '%s';",
                                                                datab->id_db);
        mx_table_setting(db, sql, message_sending, datab);
    }
}

json_object *mx_if_send_message(json_object *jobj, sqlite3 *db,
                                                            t_datab *datab) {
    json_object *j_answer = json_object_new_object();
    datab->j_result = json_object_new_array();
    char sql[255];

    if (mx_is_active(jobj, db, datab)) {
        mx_add_str_to_js(j_answer, "Answer", "Message is sent!");
        datab->message_db = mx_js_to_str(jobj, "Message");
        datab->login_db2 = mx_js_to_str(jobj, "Chat_name");
        datab->chat_name = mx_strdup(datab->login_db2);
        mx_find_chat_name(db, datab, sql);
        db_handler_for_message(db, datab, sql);
    }
    else
        mx_add_str_to_js(datab->j_result, "Answer", MX_CHEAT_MESSAGE);
    mx_strdel(&datab->id);// comment in mx_is_activ
    mx_strdel(&datab->chat_id);
    mx_strdel(&datab->chat_name);
    datab->logtrigger = 0;
    return j_answer;
}
