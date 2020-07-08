#include "dbase.h"

static int cb_id_finder(void *datab, int argc, char **argv, char **azColName) {
    (void)argc;
    (void)azColName;
    if (datab) {
        t_datab *new_datab = (t_datab *)datab;

        if (!mx_strcmp(new_datab->login_db, argv[1])) {
            new_datab->id = mx_strdup(argv[0]);
            return 1;
        }
    }
    return 0;
}

static int cb_check_acty(void *datab, int argc, char **argv,
                                                            char **azColName) {
    (void)argc;
    (void)azColName;
    if (datab) {
        t_datab *new_datab = (t_datab *)datab;

        if (!mx_strcmp(new_datab->id, argv[0])
            && !mx_strcmp(new_datab->security_db, argv[1])) {
            new_datab->passtrigger = 1;
            return 1;
        }
    }
    return 0;
}

bool mx_is_active(json_object *jobj, sqlite3 *db, t_datab *datab) {
    bool result = false;
    char sql[255];

    datab->login_db = mx_js_to_str(jobj, "Login");
    datab->security_db = mx_js_to_str(jobj, "Security_key");
    if (datab->login_db && datab->security_db) {
        sprintf(sql, "select ID, LOGIN from USERS;");
        mx_table_setting(db, sql, cb_id_finder, datab);
        sprintf(sql, "select USER_id, SECURITY_KEY from ACTIVITY;");
        mx_table_setting(db, sql, cb_check_acty, datab);
        if (datab->passtrigger == 1) {
            datab->passtrigger = 0;
            result = true;
        }
    }
    // datab->id must be freed in the fuction where 'mx_is_active' called
    return result;
}
