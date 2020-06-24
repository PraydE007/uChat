#include "dbase.h"

static int cb_reganswer(void *datab, int argc, char **argv, char **azColName) {
    (void)argc;
    (void)azColName;
    if (datab) {
        t_datab *new_datab = (t_datab *)datab;

        if (!mx_strcmp(new_datab->login_db, argv[0])) {
            new_datab->logtrigger = 1;
            return 1;
        }
    }
    return 0;
}

json_object *mx_if_registr(json_object *jobj, sqlite3 *db, t_datab *datab) {
    json_object *j_result = json_object_new_object();
    int connection_point;
    char *err = NULL;
    char sql[1024];

    datab->login_db = mx_json_to_str(jobj, "Login");
    sprintf(sql, "select LOGIN from USERS;");
    connection_point = sqlite3_exec(db, sql, cb_reganswer, datab, &err);
    if (datab->logtrigger == 1)
        mx_js_add(j_result, "Answer", MX_ERRREG);
    else {
        mx_users_insert(jobj, db);
        mx_js_add(j_result, "Answer", MX_REG);
    }
    printf("answer: %s\n", mx_json_to_str(j_result, "Answer"));
    datab->logtrigger = 0;
    return j_result;
}
