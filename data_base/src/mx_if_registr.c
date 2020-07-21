#include "dbase.h"

static void insert_user(json_object *jobj, json_object *j_result, sqlite3 *db,
                                                                    char *sql) {
    if (mx_js_to_str(jobj, "Login") && mx_js_to_str(jobj, "Passwd")
        && mx_js_to_str(jobj, "Email") && mx_js_to_str(jobj, "Mobile")) {
        sprintf(sql, "insert into USERS (LOGIN, PASSWORD, EMAIL, MOBILE)" \
                "values('%s', '%s', '%s', '%s')", mx_js_to_str(jobj, "Login"),
                mx_js_to_str(jobj, "Passwd"), mx_js_to_str(jobj, "Email"),
                mx_js_to_str(jobj, "Mobile"));
        mx_table_creation(db, sql, mx_callback);
        mx_add_str_to_js(j_result, "Answer", MX_REG_MES);
    }
    else
        mx_add_str_to_js(j_result, "Answer", MX_CHEAT_MESSAGE);
}

json_object *mx_if_registr(json_object *jobj, sqlite3 *db, t_datab *datab) {
    json_object *j_result = json_object_new_object();
    char sql[255];

    datab->login_db = mx_js_to_str(jobj, "Login");
    datab->chat_name = mx_strdup(datab->login_db);
    if (mx_check_login_on_server(db, datab, datab->login_db)
        || mx_is_chat(db, sql, datab))
        mx_add_str_to_js(j_result, "Answer", MX_REG_CHAT_ERR);
    else
        insert_user(jobj, j_result, db, sql);
    datab->logtrigger = 0;
    mx_strdel(&datab->chat_name);
    return j_result;
}
