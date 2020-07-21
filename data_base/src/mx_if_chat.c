#include "dbase.h"

json_object *mx_if_chat(json_object *jobj, sqlite3 *db, t_datab *datab) {
    json_object *j_result = json_object_new_object();
    char sql[255];
    if (mx_is_active(jobj, db, datab)) {
        datab->login_db = mx_js_to_str(jobj, "Chat_name");
        datab->chat_name = mx_strdup(datab->login_db);
        if (mx_is_chat(db, sql, datab)) {
            mx_strdel(&datab->chat_name);
            j_result = mx_if_public_chat(jobj, db, datab);
        }
        else {
            mx_strdel(&datab->chat_name);
            j_result = mx_if_private_chat(jobj, db, datab);
        }
    }
    else
        mx_add_str_to_js(j_result, "Answer", MX_CHEAT_MESSAGE);
    mx_strdel(&datab->id);// comment in mx_is_active
    mx_strdel(&datab->chat_id);
    return j_result;
}
