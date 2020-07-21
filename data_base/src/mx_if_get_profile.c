#include "dbase.h"

static int cb_get_profile(void *datab, int argc, char **argv,
                                                            char **azColName) {
    (void)argc;
    (void)azColName;
    if (datab) {
        t_datab *new_datab = (t_datab *)datab;

        if (!mx_strcmp(new_datab->id, argv[0])) {
            new_datab->email = mx_strdup(argv[2]);
            new_datab->mobile = mx_strdup(argv[3]);
            return 1;
        }
    }
    return 0;
}

json_object *mx_if_get_profile(json_object *jobj, sqlite3 *db, t_datab *datab) {
    json_object *j_result = json_object_new_object();
    char sql[255];

    if (mx_is_active(jobj, db, datab)){
        sprintf(sql, "select ID, LOGIN, EMAIL, MOBILE from USERS;");
        mx_table_setting(db, sql, cb_get_profile, datab);
        mx_add_str_to_js(j_result, "Answer", "Profile info!");
        mx_add_str_to_js(j_result, "Login", (char *)datab->login_db);
        mx_add_str_to_js(j_result, "Email", datab->email);
        mx_add_str_to_js(j_result, "Mobile", datab->mobile);
    }
    else
        mx_add_str_to_js(j_result, "Answer", MX_CHEAT_MESSAGE);
    mx_strdel(&datab->id);// comment in mx_is_active
    mx_strdel(&datab->email);
    mx_strdel(&datab->mobile);
    return j_result;
}
