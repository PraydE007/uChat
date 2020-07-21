#include "dbase.h"

static void insert_chat(json_object *j_reslt, sqlite3 *db, t_datab *datab) {
    char sql[255];

    sprintf(sql, "insert into CHATS (CHAT_NAME, CHAT_STATUS)" \
            "values('%s', '%s')", datab->chat_name, "public");
    mx_table_creation(db, sql, mx_callback);
    sprintf(sql, "select ID from CHATS where CHAT_NAME = '%s';",
            datab->login_db2);
    mx_table_setting(db, sql, mx_cb_find_chat_id, datab);
    sprintf(sql, "insert into USERS_CHATS (USER_id, CHAT_id, USER_status)" \
            "values('%s', '%s', 'admin')", datab->id, datab->chat_id);
    mx_table_creation(db, sql, mx_callback);
    mx_add_str_to_js(j_reslt, "Answer", MX_CHAT_MES);
}

json_object *mx_if_create_chat(json_object *jobj, sqlite3 *db, t_datab *datab) {
    json_object *j_result = json_object_new_object();
    char sql[30];

    if (mx_is_active(jobj, db, datab)) {
        datab->login_db2 = mx_js_to_str(jobj, "Chat_name");
        datab->chat_name = mx_strdup(datab->login_db2);
        if (mx_is_chat(db, sql, datab) || mx_is_contact(db, sql, datab))
            mx_add_str_to_js(j_result, "Answer", MX_REG_CHAT_ERR);
        else
            insert_chat(j_result, db, datab);
    }
    else
        mx_add_str_to_js(j_result, "Answer", MX_CHEAT_MESSAGE);
    mx_strdel(&datab->id);// comment in mx_is_activ
    mx_strdel(&datab->chat_name);
    datab->logtrigger = 0;
    return j_result;
}
