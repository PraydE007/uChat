#include "dbase.h"

static int callback(void *datab, int argc, char **argv, char **azColName) {
    t_datab *new_datab = (t_datab *)datab;

    (void)argc;
    (void)azColName;
    if (!mx_strcmp(new_datab->login_db, argv[0])) {
        new_datab->logtrigger = 1;
        if (!mx_strcmp(new_datab->password_db, argv[1]))
            new_datab->passtrigger = 1;
        return 1;
    }
    return 0;
}

json_object *mx_if_logging(json_object *jobj, sqlite3 *db, t_datab *datab) {
    json_object *j_result = json_object_new_object();
    int connection_point;
    char *err = NULL;
    char sql[50];

    datab->login_db = mx_json_to_str(jobj, "Login");
    datab->password_db = mx_json_to_str(jobj, "Passwd");
    sprintf(sql, "select LOGIN, PASSWORD from USERS;");
    connection_point = sqlite3_exec(db, sql, callback, datab, &err);
    if (err != SQLITE_OK)
        fprintf(stderr, "error: %s\n", sqlite3_errmsg(db));
    if (datab->logtrigger == 1 && datab->passtrigger == 1)
        mx_js_add(j_result, "Answer", MX_LOG);
    else
        mx_js_add(j_result, "Answer", MX_ERRLOG);
    datab->logtrigger = 0;
    datab->passtrigger = 0;
    return j_result;
}
