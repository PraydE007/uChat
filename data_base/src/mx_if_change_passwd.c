#include "dbase.h"

static int cb_change_psswd(void *datab, int argc, char **argv,
                                                            char **azColName) {
    (void)argc;
    (void)azColName;
    if (datab) {
        t_datab *new_datab = (t_datab *)datab;

        if (!mx_strcmp(new_datab->password_db, argv[1])) {
            new_datab->passtrigger = 1;
            return 1;
        }
    }
    return 0;
}

static void json_profile_add(json_object *j_result, t_datab *datab) {
        mx_js_add(j_result, "Answer", "The password were changed!");
        mx_js_add(j_result, "Passwd", (char *)datab->password_db);
}

static void passwd_update(json_object *jobj, sqlite3 *db, char *sql,
                                                            t_datab *datab) {
        datab->password_db = mx_json_to_str(jobj, "New_passwd");
        sprintf(sql, "update USERS set PASSWORD = '%s' where ID = '%s'",
                datab->password_db, datab->id);
        mx_table_creation(db, sql, mx_callback);
}

json_object *mx_if_change_passwd(json_object *jobj, sqlite3 *db,
                                                            t_datab *datab) {
    json_object *j_result = json_object_new_object();
    char sql[255];

    datab->password_db = mx_json_to_str(jobj, "Passwd");
    if (mx_is_active(jobj, db, datab)) {
        sprintf(sql, "select ID, PASSWORD from USERS where ID = '%s';", datab->id);
        mx_table_setting(db, sql, cb_change_psswd, datab);
        if (datab->passtrigger == 1) {
            passwd_update(jobj, db, sql, datab);
            // datab->password_db = mx_json_to_str(jobj, "New_passwd");
            // sprintf(sql, "update USERS set PASSWORD = '%s' where ID = '%s'",
            //         datab->password_db, datab->id);
            // mx_table_creation(db, sql, mx_callback);
            json_profile_add(j_result, datab);
        }
        else
            mx_js_add(j_result, "Answer", "Wrong password!");
    }
    else
        mx_js_add(j_result, "Answer", MX_CHEAT_MESSAGE);
printf("mx_if_change_passwd(j_result): %s\n", json_object_to_json_string(j_result));//
    mx_strdel(&datab->id);// comment in mx_is_active
    datab->passtrigger = 0;
    return j_result;
}
