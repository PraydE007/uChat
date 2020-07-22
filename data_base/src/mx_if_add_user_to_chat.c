#include "dbase.h"

static int cb_find_chat_id_and_status(void *datab, int argc, char **argv,
                                      char **azColName) {
    (void)argc;
    (void)azColName;
    if (datab) {
        t_datab *new_datab = (t_datab *)datab;

        new_datab->chat_id = mx_strdup(argv[0]);
        new_datab->chat_status = mx_strdup(argv[1]);
    }
    return 0;
}

static int cb_find_contact_id_in_chat(void *datab, int argc, char **argv,
                                      char **azColName) {
    (void)argc;
    (void)azColName;
    if (datab) {
        t_datab *new_datab = (t_datab *)datab;

        if (!mx_strcmp(new_datab->second_id, argv[0])) {
            new_datab->passtrigger = 1;
            return 1;
        }
    }
    return 0;
}

static void insert_contact_in_to_chat(sqlite3 *db, char *sql, t_datab *datab) {
    sprintf(sql, "insert into USERS_CHATS (USER_id, CHAT_id, USER_status)" \
            "values('%s', '%s', 'member')", datab->second_id, datab->chat_id);
    mx_table_creation(db, sql, mx_callback);
    mx_add_str_to_js(datab->j_result, "Answer", MX_CONT_ADD_CHAT);
    mx_find_chat_contact_list(db, datab, sql);
    datab->message_db = "You were added to the chat!";
    sprintf(sql, "select SOCKET from ACTIVITY where USER_id = '%s';",
                                                            datab->second_id);
    mx_table_setting(db, sql, mx_cb_chat_notification, datab);
    mx_strdel(&datab->second_id);
}

static void condition_for_chat(sqlite3 *db, t_datab *datab, char *sql) {
    sprintf(sql, "select ID, LOGIN from USERS;");
    mx_table_setting(db, sql, mx_cb_find_user_id, datab);
    if (datab->second_id) {
        sprintf(sql, "select USER_id from USERS_CHATS " \
                "where CHAT_id = %s;", datab->chat_id);
        mx_table_setting(db, sql, cb_find_contact_id_in_chat, datab);
        if (!mx_strcmp(datab->login_db, datab->login_db2))
            mx_add_str_to_js(datab->j_result, "Answer", "You can not add " \
                            "yourself into chat!");
        else if (datab->passtrigger == 1)
            mx_add_str_to_js(datab->j_result, "Answer", "You have already " \
                            "this contact in the chat!");
        else if (datab->logtrigger == 1)
            insert_contact_in_to_chat(db, sql, datab);
    }
    else
        mx_add_str_to_js(datab->j_result, "Answer", MX_CONT_ERR);
    mx_strdel(&datab->chat_id);
    datab->logtrigger = 0;
    datab->passtrigger = 0;
}

json_object *mx_if_add_user_to_chat(json_object *jobj, sqlite3 *db,
                                    t_datab *datab) {
    datab->j_result = json_object_new_object();
    char sql[255];

    if (mx_is_active(jobj, db, datab)) {
        datab->login_db2 = mx_js_to_str(jobj, "Contact_login");
        datab->chat_name_db = mx_js_to_str(jobj, "Chat_name");
        sprintf(sql, "select ID, CHAT_STATUS from CHATS " \
                "where CHAT_NAME = '%s';", datab->chat_name_db);
        mx_table_setting(db, sql, cb_find_chat_id_and_status, datab);
        if (!mx_strcmp(datab->chat_status, "public"))
            condition_for_chat(db, datab, sql);
        else
            mx_add_str_to_js(datab->j_result, "Answer", MX_PRIVATE_CHAT);
    }
    else
        mx_add_str_to_js(datab->j_result, "Answer", MX_CHEAT_MESSAGE);
    mx_strdel(&datab->id);// comment in mx_is_active
    mx_strdel(&datab->chat_status);
    return datab->j_result;
}
