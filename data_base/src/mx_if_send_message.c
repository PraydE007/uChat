#include "dbase.h"

static int cb_users_id_for_chat(void *datab, int argc, char **argv,
                                                            char **azColName) {
    (void)argc;
    (void)azColName;
    if (datab) {
        json_object *j_message = json_object_new_object();
        json_object *new_datab = (json_object *)datab;
        mx_js_add_str(j_message, "Message", argv[0]);
        mx_js_arr_add(new_datab, j_message);
        json_object_put(j_message);
    }
    return 0;
}

// static void if_active(json_object *jobj, json_object *j_result, sqlite3 *db,
//                                                             t_datab *datab) {
//     json_object *j_answer = json_object_new_object();
//     char sql[255];

//     mx_js_add_str(j_answer, "Answer", "Message history!");
//     mx_js_arr_add(j_result, j_answer);
//     datab->login_db2 = mx_json_to_str(jobj, "Chat_name");
//     sprintf(sql, "select ID from CHATS where CHAT_NAME = '%s';",
//             datab->login_db2);
//     mx_table_setting(db, sql, mx_cb_chat_id_finder, datab);
//     sprintf(sql, "select MESSAGE_text from MESSAGES where CHAT_id = '%s' " \
//             "order by ID desc limit 2;", datab->chat_id);
//     mx_table_setting(db, sql, cb_massege_history, j_result);
//     json_object_put(j_answer);
// }

json_object *mx_if_send_message(json_object *jobj, sqlite3 *db, t_datab *datab) {
    // json_object *j_answer = json_object_new_object();
    json_object *j_result = json_object_new_array();
    char sql[100];

    if (mx_is_active(jobj, db, datab)) {
        // if_active(jobj, j_result, db, datab);
        mx_js_add_str(j_answer, "Answer", "Message is sent!");
        // mx_js_arr_add(j_result, j_answer);
        datab->login_db2 = mx_json_to_str(jobj, "Chat_name");
        sprintf(sql, "select ID from CHATS where CHAT_NAME = '%s';",
                datab->login_db2);
        mx_table_setting(db, sql, mx_cb_chat_id_finder, datab);
        sprintf(sql, "select USER_id from USERS_CHATS where CHAT_id = '%s';",
                                                                datab->chat_id);
        mx_table_setting(db, sql, cb_massege_history, j_result);
    }
    else
        mx_js_add_str(j_result, "Answer", MX_CHEAT_MESSAGE);
    mx_strdel(&datab->id);// comment in mx_is_activ
    mx_strdel(&datab->chat_id);
    datab->logtrigger = 0;
    return j_result;
}