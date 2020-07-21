#include "dbase.h"

static void insert_message(json_object *jobj, json_object *receive_message,
                                                sqlite3 *db, t_datab *datab) {
    char sql[4096];

    if (!mx_strcmp("File", mx_js_to_str(jobj, "Type"))) {
        datab->fsize_db = mx_js_to_str(jobj, "Size");
        sprintf(sql, "insert into MESSAGES (SENDER_id, CHAT_id, MESSAGE_text," \
                " IS_file, FILE_size) values('%s', '%s', '%s', 'true', '%s')",
                datab->id, datab->chat_id, datab->message_db, datab->fsize_db);
        mx_add_str_to_js(receive_message, "File_message",
                        (char *)datab->message_db);
        mx_add_str_to_js(receive_message, "File_size", (char *)datab->fsize_db);
    }
    else {
        sprintf(sql, "insert into MESSAGES (SENDER_id, CHAT_id, MESSAGE_text, "\
                "IS_file) values('%s', '%s', '%s', 'false')", datab->id,
                datab->chat_id, datab->message_db);
        mx_add_str_to_js(receive_message, "Message", (char *)datab->message_db);
    }
    mx_table_creation(db, sql, mx_callback);
}

static void receive_js_and_insert_message
(json_object *jobj, json_object *receive_message, sqlite3 *db, t_datab *datab) {
    if (datab->logtrigger == 1
        && !mx_strcmp("File", mx_js_to_str(jobj, "Type")))
        mx_add_str_to_js(receive_message, "Answer", "Receive_file");
    else if (datab->logtrigger == 1)
        mx_add_str_to_js(receive_message, "Answer", "Receive_message");
    else {
        if (!mx_strcmp("File", mx_js_to_str(jobj, "Type")))
            mx_add_str_to_js(receive_message, "Answer", "Public_receive_file");
        else
            mx_add_str_to_js(receive_message, "Answer",
                            "Public_receive_message");
        mx_add_str_to_js(receive_message, "Chat_name", datab->chat_name);
    }
    mx_add_str_to_js(receive_message, "Sender", (char *)datab->login_db);
    insert_message(jobj, receive_message, db, datab);
    datab->logtrigger = 0;
}

static void message_sending_cycle(json_object *jobj, sqlite3 *db,
                                  t_datab *datab) {
    char sql[255];
    json_object *message_for_user = NULL;

    for (int i = 0; i < datab->lenth; i++) {
        message_for_user = json_tokener_parse(datab->buffer_db);
        datab->id_db = mx_js_arr_to_str(datab->j_result, i);
        mx_js_chts_conts_for_receiver(message_for_user, db, datab, sql);
        datab->message_db = json_object_get_string(message_for_user);
        sprintf(sql, "select SOCKET from ACTIVITY where USER_id = '%s';",
                                                                datab->id_db);
        mx_table_setting(db, sql, mx_cb_message_sending, datab);
        datab->message_db = mx_js_to_str(jobj, "Message");
        json_object_put(message_for_user);
    }
}

static void db_handler_for_message
(json_object *jobj, json_object *receive_message, sqlite3 *db, t_datab *datab) {
    char sql[255];

    sprintf(sql, "select ID from CHATS where CHAT_NAME = '%s';",
            datab->chat_name);
    mx_table_setting(db, sql, mx_cb_find_chat_id, datab);
    sprintf(sql, "select USER_id from USERS_CHATS where CHAT_id = '%s' " \
            "and USER_id != '%s';", datab->chat_id, datab->id);
    mx_table_setting(db, sql, mx_cb_find_user_ids_for_chat, datab->j_result);
    if (!mx_strcmp("File", mx_js_to_str(jobj, "Type")))
        datab->fpath_db = mx_strjoin("server/tmp/", datab->message_db);
    receive_js_and_insert_message(jobj, receive_message, db, datab);
    datab->buffer_db = json_object_get_string(receive_message);
    datab->lenth = json_object_array_length(datab->j_result);
    message_sending_cycle(jobj, db, datab);
}

json_object *mx_if_send_message(json_object *jobj, sqlite3 *db,
                                                            t_datab *datab) {
    json_object *receive_message = json_object_new_object();
    json_object *j_answer = json_object_new_object();
    datab->j_result = json_object_new_array();
    char sql[255];

    if (mx_is_active(jobj, db, datab)) {
        mx_add_str_to_js(j_answer, "Answer", "Message is sent!");
        datab->message_db = mx_js_to_str(jobj, "Message");
        datab->login_db2 = mx_js_to_str(jobj, "Chat_name");
        datab->chat_name = mx_strdup(datab->login_db2);
        mx_find_chat_name(db, datab, sql);
        db_handler_for_message(jobj, receive_message, db, datab);
    }
    else
        mx_add_str_to_js(datab->j_result, "Answer", MX_CHEAT_MESSAGE);
    mx_strdel(&datab->id);// comment in mx_is_activ
    mx_strdel(&datab->chat_id);
    mx_strdel(&datab->chat_name);
    json_object_put(receive_message);
    return j_answer;
}
