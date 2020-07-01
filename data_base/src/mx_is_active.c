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

static int cb_check_activity(void *datab, int argc, char **argv,
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
    int connection_point;
    bool result = false;
    char sql[255];

    datab->login_db = mx_json_to_str(jobj, "Login");
    datab->security_db = mx_json_to_str(jobj, "Security_key");
    sprintf(sql, "select ID, LOGIN from USERS;");
    connection_point = sqlite3_exec(db, sql, cb_id_finder, datab, NULL);
    if (connection_point != SQLITE_OK && connection_point != SQLITE_ABORT)
        fprintf(stderr, "error: %s\n", sqlite3_errmsg(db));
    sprintf(sql, "select USER_id, SECURITY_KEY from ACTIVITY;");
    connection_point = sqlite3_exec(db, sql, cb_check_activity, datab, NULL);
    if (connection_point != SQLITE_OK && connection_point != SQLITE_ABORT)
        fprintf(stderr, "error: %s\n", sqlite3_errmsg(db));
    if (datab->passtrigger == 1)
        result = true;
    // datab->id must be freed in the fuction where 'mx_is_active' called
    datab->passtrigger = 0;
    return result;
}
