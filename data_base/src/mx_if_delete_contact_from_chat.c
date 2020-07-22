#include "dbase.h"

static void delete_contact_rfom_the_chat(sqlite3 *db, char *sql,
                                         t_datab *datab) {
    sprintf(sql, "delete from USERS_CHATS where USER_id = %s " \
            "and CHAT_id = %s;", datab->second_id, datab->chat_id);
    mx_table_creation(db, sql, mx_callback);
    mx_add_str_to_js(datab->j_result, "Answer", MX_DEL_CHAT_MES);
    mx_find_chat_contact_list(db, datab, sql);
    datab->db = db;
    datab->id_db = datab->second_id;
    datab->message_db = "You were deleted from the chat!";
    sprintf(sql, "select SOCKET from ACTIVITY where USER_id = '%s';",
            datab->second_id);
    mx_table_setting(db, sql, mx_cb_chat_notification, datab);
    mx_strdel(&datab->second_id);
}

static void condition_for_admin(json_object *jobj, sqlite3 *db,
                                t_datab *datab, char *sql) {
    datab->login_db2 = mx_js_to_str(jobj, "Contact_login");
    sprintf(sql, "select ID, LOGIN from USERS");
    mx_table_setting(db, sql, mx_cb_find_user_id, datab);
    sprintf(sql, "select ID from CHATS where CHAT_NAME = '%s';",
            datab->chat_name_db);
    mx_table_setting(db, sql, mx_cb_find_chat_id, datab);
    if (mx_is_chat_member(db, datab, sql)) {
        if(!mx_strcmp(datab->id, datab->second_id))
            mx_chat_deleting(db, datab, sql);
        else
            delete_contact_rfom_the_chat(db, sql, datab);
    }
    else
        mx_add_str_to_js(datab->j_result, "Answer", MX_ERR_CHAT_MEMBER);
}

json_object *mx_if_delete_contact_from_chat(json_object *jobj, sqlite3 *db,
                                            t_datab *datab) {
    datab->j_result = json_object_new_object();
    char sql[255];

    if (mx_is_active(jobj, db, datab)) {
        datab->chat_name_db = mx_js_to_str(jobj, "Chat_name");
        if (mx_is_admin(db, datab, sql))
            condition_for_admin(jobj, db, datab, sql);
        else
            mx_add_str_to_js(datab->j_result, "Answer", MX_ERR_DEL_CHAT);
    }
    else
        mx_add_str_to_js(datab->j_result, "Answer", MX_CHEAT_MESSAGE);
    mx_strdel(&datab->id);// comment in mx_is_active
    mx_strdel(&datab->chat_id);
    mx_strdel(&datab->second_id);
    datab->logtrigger = 0;
    return datab->j_result;
}
