#include "dbase.h"

static void profile_insert(json_object *j_result, sqlite3 *db, t_datab *datab) {
    char sql[255];

    mx_add_str_to_js(j_result, "Answer", "Profile data are changed!");
    if (mx_strcmp(datab->login_db2, "")) {
        sprintf(sql, "update USERS set LOGIN = '%s', EMAIL = '%s', " \
                "MOBILE = '%s', SOCKET = %d where ID = '%s'", datab->login_db2,
                datab->email_db, datab->mobile_db, datab->socket, datab->id);
        mx_add_str_to_js(j_result, "Login", (char *)datab->login_db2);
    }
    else {
        sprintf(sql, "update USERS set LOGIN = '%s', EMAIL = '%s', " \
                "MOBILE = '%s', SOCKET = %d where ID = '%s'", datab->login_db,
                datab->email_db, datab->mobile_db, datab->socket, datab->id);
        mx_add_str_to_js(j_result, "Login", (char *)datab->login_db);
    }
    mx_add_str_to_js(j_result, "Email", (char *)datab->email_db);
    mx_add_str_to_js(j_result, "Mobile", (char *)datab->mobile_db);
    mx_table_creation(db, sql, mx_callback);
}

json_object *mx_if_change_profile(json_object *jobj, sqlite3 *db,
                                                            t_datab *datab) {
    json_object *j_result = json_object_new_object();

    datab->socket = mx_js_to_int(jobj, "Socket");
    datab->login_db2 = mx_js_to_str(jobj, "New_login");
    datab->email_db = mx_js_to_str(jobj, "Email");
    datab->mobile_db = mx_js_to_str(jobj, "Mobile");
    if (mx_is_active(jobj, db, datab)) {
        if (!mx_check_login_on_server(db, datab, datab->login_db2))
            profile_insert(j_result, db, datab);
        else
            mx_add_str_to_js(j_result, "Answer", MX_REG_CHAT_ERR);
    }
    else
        mx_add_str_to_js(j_result, "Answer", MX_CHEAT_MESSAGE);
// printf("mx_if_change_profile(j_result): %s\n", json_object_to_json_string(j_result));//
    mx_strdel(&datab->id);// comment in mx_is_active
    return j_result;
}
