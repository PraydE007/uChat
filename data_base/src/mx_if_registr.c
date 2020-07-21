#include "dbase.h"

// static int cb_reganswer(void *datab, int argc, char **argv, char **azColName) {
//     (void)argc;
//     (void)azColName;
//     if (datab) {
//         t_datab *new_datab = (t_datab *)datab;

//         if (!mx_strcmp(new_datab->login_db, argv[0])) {
//             new_datab->logtrigger = 1;
//             return 1;
//         }
//     }
//     return 0;
// }

static void insert_user(json_object *jobj, json_object *j_reslt, sqlite3 *db,
                                                                    char *sql) {
    // int connection_point;

    sprintf(sql, "insert into USERS (LOGIN, PASSWORD, EMAIL, MOBILE)" \
            "values('%s', '%s', '%s', '%s')", mx_js_to_str(jobj, "Login"),
            mx_js_to_str(jobj, "Passwd"), mx_js_to_str(jobj, "Email"),
            mx_js_to_str(jobj, "Mobile"));
    mx_table_creation(db, sql, mx_callback);
    // connection_point = sqlite3_exec(db, sql, mx_callback, NULL, NULL);
    // if (connection_point != SQLITE_OK)
    //     fprintf(stderr, "error: %s\n", sqlite3_errmsg(db));
    mx_add_str_to_js(j_reslt, "Answer", MX_REG_MES);
}

json_object *mx_if_registr(json_object *jobj, sqlite3 *db, t_datab *datab) {
    json_object *j_result = json_object_new_object();
    // int connection_point;
    char sql[255];

    datab->login_db = mx_js_to_str(jobj, "Login");
    datab->chat_name = mx_strdup(datab->login_db);
    // sprintf(sql, "select LOGIN from USERS;");
    // mx_table_setting(db, sql, cb_reganswer, datab);
    // connection_point = sqlite3_exec(db, sql, cb_reganswer, datab, NULL);
    // if (connection_point != SQLITE_OK && connection_point != SQLITE_ABORT)
    //     fprintf(stderr, "error: %s\n", sqlite3_errmsg(db));
    if (mx_check_login_on_server(db, datab, datab->login_db)
        || mx_is_chat(db, sql, datab))
        mx_add_str_to_js(j_result, "Answer", MX_REG_CHAT_ERR);
    else
        insert_user(jobj, j_result, db, sql);
// printf("answer: %s\n", mx_js_to_str(j_result, "Answer")); //
    datab->logtrigger = 0;
    mx_strdel(&datab->chat_name);
    return j_result;
}
