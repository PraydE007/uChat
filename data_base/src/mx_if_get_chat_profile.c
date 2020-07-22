#include "dbase.h"

json_object *mx_if_get_chat_profile(json_object *jobj, sqlite3 *db,
                                    t_datab *datab) {
    datab->j_result = json_object_new_object();
    char sql[255];

    if (mx_is_active(jobj, db, datab)){
        datab->chat_name_db = mx_js_to_str(jobj, "Chat_name");
        sprintf(sql, "select ID from CHATS where CHAT_NAME = '%s';",
                datab->chat_name_db);
        mx_table_setting(db, sql, mx_cb_find_chat_id, datab);
        mx_add_str_to_js(datab->j_result, "Answer", "Chat profile info!");
        mx_add_str_to_js(datab->j_result, "Chat_name",
                        (char *)datab->chat_name_db);
        mx_find_chat_contact_list(db, datab, sql);
    }
    else
        mx_add_str_to_js(datab->j_result, "Answer", MX_CHEAT_MESSAGE);
    mx_strdel(&datab->id);// comment in mx_is_active
    mx_strdel(&datab->chat_id);
    return datab->j_result;
}
