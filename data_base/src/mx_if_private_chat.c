#include "dbase.h"

static int cb_massege_history(void *datab, int argc, char **argv,
                                                            char **azColName) {
    (void)argc;
    (void)azColName;
    if (datab) {
        json_object *j_message = json_object_new_object();
        t_datab *new_datab = (t_datab *)datab;
        char *login = mx_find_user_login(new_datab->db, argv[0]);

        mx_add_str_to_js(j_message, "Login", login);
        if (!mx_strcmp(new_datab->id, argv[0]) && !mx_strcmp("true", argv[2]))
            mx_add_str_to_js(j_message, "Own_file", argv[1]);
        else if (!mx_strcmp(new_datab->id, argv[0]))
            mx_add_str_to_js(j_message, "Own_message", argv[1]);
        else if (!mx_strcmp("true", argv[2]))
            mx_add_str_to_js(j_message, "File", argv[1]);
        else
            mx_add_str_to_js(j_message, "Message", argv[1]);
        mx_add_arr_to_js(new_datab->j_result, j_message);
        mx_strdel(&login);
    }
    return 0;
}

static void if_active(json_object *jobj, json_object *j_answer, sqlite3 *db,
                                                            t_datab *datab) {
    char sql[255];

    mx_add_str_to_js(j_answer, "Answer", "Private message history!");
    datab->login_db2 = mx_js_to_str(jobj, "Chat_name");
    datab->chat_name = mx_strjoin(datab->login_db, datab->login_db2);
    if (!mx_is_chat(db, sql, datab)) {
        mx_strdel(&datab->chat_name);
        datab->chat_name = mx_strjoin(datab->login_db2, datab->login_db);
    }
    sprintf(sql, "select ID from CHATS where CHAT_NAME = '%s';",
            datab->chat_name);
    mx_table_setting(db, sql, mx_cb_find_chat_id, datab);
    sprintf(sql, "select SENDER_id, MESSAGE_text, IS_file from MESSAGES where" \
            " CHAT_id = '%s' order by ID;", datab->chat_id);
    mx_table_setting(db, sql, cb_massege_history, datab);
    json_object_object_add(j_answer, "Array", (datab)->j_result);
    mx_strdel(&datab->chat_name);
}

json_object *mx_if_private_chat(json_object *jobj, sqlite3 *db,
                                                            t_datab *datab) {
    json_object *j_answer = json_object_new_object();
    datab->j_result = json_object_new_array();
    datab->db = db;

    if (mx_is_active(jobj, db, datab))
        if_active(jobj, j_answer, db, datab);
    else
        mx_add_str_to_js(datab->j_result, "Answer", MX_CHEAT_MESSAGE);
    mx_strdel(&datab->id);// comment in mx_is_activ
    mx_strdel(&datab->chat_id);
    datab->logtrigger = 0;
    return j_answer;
}
