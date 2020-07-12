#include "dbase.h"

static void chat_changing(json_object *j_result, sqlite3 *db, t_datab *datab,
                                                                    char *sql) {

    mx_add_str_to_js(j_result, "Answer", "Chat name is changed!");
    sprintf(sql, "update CHATS set CHAT_NAME = '%s' where ID = '%s'",
    datab->login_db2, datab->chat_id);
    mx_add_str_to_js(j_result, "New_chat_name", (char *)datab->login_db2);
    // mx_add_str_to_js(j_result, "Login", (char *)datab->login_db);
    
    // mx_add_str_to_js(j_result, "Email", (char *)datab->email_db);
    // mx_add_str_to_js(j_result, "Mobile", (char *)datab->mobile_db);
    mx_table_creation(db, sql, mx_callback);
}

json_object *mx_if_change_chat(json_object *jobj, sqlite3 *db,
                                                            t_datab *datab) {
    json_object *j_result = json_object_new_object();
    char sql[255];

    if (mx_is_active(jobj, db, datab)) {
        datab->login_db = mx_js_to_str(jobj, "Chat_name");
        datab->login_db2 = mx_js_to_str(jobj, "New_chat_name");
        datab->chat_name = mx_strdup(datab->login_db2);
        if (!mx_is_chat(db, sql, datab) && !mx_is_contact(db, sql, datab)) {
            sprintf(sql, "select ID from CHATS where CHAT_NAME = '%s';",
                    datab->login_db);
            mx_table_setting(db, sql, mx_cb_find_chat_id, datab);
            chat_changing(j_result, db, datab, sql);
        }
        else
            mx_add_str_to_js(j_result, "Answer", MX_REG_CHAT_ERR);
    }
    else
        mx_add_str_to_js(j_result, "Answer", MX_CHEAT_MESSAGE);
printf("mx_if_change_profile(j_result): %s\n", json_object_to_json_string(j_result));//
    mx_strdel(&datab->id);// comment in mx_is_active
    mx_strdel(&datab->chat_name);
    return j_result;
}
