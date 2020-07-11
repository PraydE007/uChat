#include "dbase.h"

static void contact_deleting(json_object *jobj, json_object *j_result,
                                                sqlite3 *db, t_datab *datab) {
    char sql[255];

    datab->login_db2 = mx_js_to_str(jobj, "Contact_login");
    sprintf(sql, "select ID, LOGIN from USERS;");
    mx_table_setting(db, sql, mx_cb_find_user_id, datab);
    sprintf(sql, "delete from CONTACTS where OWNER_id = %s " \
            "and FOLLOWER_id = %s;", datab->id, datab->second_id);
    mx_table_creation(db, sql, mx_callback);
    datab->chat_name = mx_strdup(datab->login_db2);
    mx_find_chat_name(db, datab, sql);
    sprintf(sql, "select ID from CHATS where CHAT_NAME = '%s';",
            datab->chat_name);
    mx_table_setting(db, sql, mx_cb_find_chat_id, datab);
    sprintf(sql, "delete from USERS_CHATS where USER_id = %s " \
            "and CHAT_id = %s;", datab->id, datab->chat_id);
    mx_table_creation(db, sql, mx_callback);
    mx_add_str_to_js(j_result, "Answer", "The contact was deleted!");
    mx_js_chts_conts(j_result, db, datab, sql);
}

json_object *mx_if_delete_contact(json_object *jobj, sqlite3 *db,
                                                            t_datab *datab) {
    json_object *j_result = json_object_new_object();
    // char sql[255];

    if (mx_is_active(jobj, db, datab)) {
        contact_deleting(jobj, j_result, db, datab);
        // datab->login_db2 = mx_js_to_str(jobj, "Contact_login");
        // sprintf(sql, "select ID, LOGIN from USERS;");
        // mx_table_setting(db, sql, mx_cb_find_user_id, datab);
        // sprintf(sql, "delete from CONTACTS where OWNER_id = %s " \
        //         "and FOLLOWER_id = %s;", datab->id, datab->second_id);
        // mx_table_creation(db, sql, mx_callback);
        // datab->chat_name = mx_strdup(datab->login_db2);
        // mx_find_chat_name(db, datab, sql);
        // sprintf(sql, "select ID from CHATS where CHAT_NAME = '%s';",
        //         datab->chat_name);
        // mx_table_setting(db, sql, mx_cb_find_chat_id, datab);
        // sprintf(sql, "delete from USERS_CHATS where USER_id = %s " \
        //         "and CHAT_id = %s;", datab->id, datab->chat_id);
        // mx_table_creation(db, sql, mx_callback);
        // mx_add_str_to_js(j_result, "Answer", "The contact was deleted!");
        // mx_js_chts_conts(j_result, db, datab, sql);
    }
    else
        mx_add_str_to_js(j_result, "Answer", MX_CHEAT_MESSAGE);
printf("if_delete_contact(j_result): %s\n", json_object_to_json_string(j_result));//
    mx_strdel(&datab->id);// comment in mx_is_active
    mx_strdel(&datab->chat_id);
    mx_strdel(&datab->chat_name);
    return j_result;
}
