#include "dbase.h"

static int cb_get_profile(void *datab, int argc, char **argv,
                                                            char **azColName) {
    (void)argc;
    (void)azColName;
    if (datab) {
        t_datab *new_datab = (t_datab *)datab;

        if (!mx_strcmp(new_datab->second_id, argv[0])) {
            new_datab->email = mx_strdup(argv[2]);
            new_datab->mobile = mx_strdup(argv[3]);
            return 1;
        }
    }
    return 0;
}

json_object *mx_if_get_contact_profile(json_object *jobj, sqlite3 *db,
                                                            t_datab *datab) {
    json_object *j_result = json_object_new_object();
    char sql[255];

    if (mx_is_active(jobj, db, datab)){
        datab->login_db2 = mx_js_to_str(jobj, "Contact_login");
        sprintf(sql, "select ID, LOGIN from USERS;");
        mx_table_setting(db, sql, mx_cb_find_user_id, datab);
        sprintf(sql, "select ID, LOGIN, EMAIL, MOBILE from USERS;");
        mx_table_setting(db, sql, cb_get_profile, datab);
        mx_add_str_to_js(j_result, "Answer", "Contact profile info!");
        mx_add_str_to_js(j_result, "Login", (char *)datab->login_db2);
        mx_add_str_to_js(j_result, "Email", datab->email);
        mx_add_str_to_js(j_result, "Mobile", datab->mobile);
    }
    else
        mx_add_str_to_js(j_result, "Answer", MX_CHEAT_MESSAGE);
printf("if_get_contact_profile: %s\n", json_object_to_json_string(j_result));//
    mx_strdel(&datab->id);// comment in mx_is_active
    mx_strdel(&datab->second_id);
    // mx_strdel(&datab->email); - it can be freed in dealloc
    // mx_strdel(&datab->mobile);
    return j_result;
}
