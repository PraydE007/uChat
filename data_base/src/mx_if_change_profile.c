#include "dbase.h"

// static int cb_get_profile(void *datab, int argc, char **argv,
//                                                             char **azColName) {
//     (void)argc;
//     (void)azColName;
//     if (datab) {
//         t_datab *new_datab = (t_datab *)datab;

//         if (!mx_strcmp(new_datab->id, argv[0])) {
//             new_datab->email = mx_strdup(argv[2]);
//             new_datab->mobile = mx_strdup(argv[3]);
//             return 1;
//         }
//     }
//     return 0;
// }

static void json_profile_add(json_object *j_result, t_datab *datab) {
        mx_js_add(j_result, "Answer", "Profile data is changed!");
        mx_js_add(j_result, "Login", (char *)datab->login_db2);
        mx_js_add(j_result, "Email", (char *)datab->email_db);
        mx_js_add(j_result, "Mobile", (char *)datab->mobile_db);
}

json_object *mx_if_change_profile(json_object *jobj, sqlite3 *db,
                                                            t_datab *datab) {
    json_object *j_result = json_object_new_object();
    char sql[255];

    datab->socket = mx_json_to_int(jobj, "Socket");
    datab->login_db2 = mx_json_to_str(jobj, "New_login");
    datab->email_db = mx_json_to_str(jobj, "Email");
    datab->mobile_db = mx_json_to_str(jobj, "Mobile");
    if (mx_is_active(jobj, db, datab)){
        sprintf(sql, "update USERS set LOGIN = %s, EMAIL = '%s', " \
                "MOBILE = '%s', SOCKET = %d where ID = '%s'", datab->login_db2,
                datab->email_db, datab->mobile_db, datab->socket, datab->id);
        mx_table_creation(db, sql, mx_callback);
        json_profile_add(j_result, datab);
        // mx_js_add(j_result, "Answer", "Profile data is changed!");
        // mx_js_add(j_result, "Login", (char *)datab->login_db2);
        // mx_js_add(j_result, "Email", (char *)datab->email_db);
        // mx_js_add(j_result, "Mobile", (char *)datab->mobile_db);
    }
    else
        mx_js_add(j_result, "Answer", MX_CHEAT_MESSAGE);
printf("mx_if_change_profile(j_result): %s\n", json_object_to_json_string(j_result));//
    mx_strdel(&datab->id);// comment in mx_is_active
    return j_result;
}
