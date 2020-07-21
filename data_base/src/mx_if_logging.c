#include "dbase.h"

static int cb_loganswer(void *datab, int argc, char **argv, char **azColName) {
    t_datab *new_datab = (t_datab *)datab;

    (void)argc;
    (void)azColName;
    if (!mx_strcmp(new_datab->login_db, argv[1])) {
        new_datab->logtrigger = 1;
        if (!mx_strcmp(new_datab->password_db, argv[2])) {
            new_datab->passtrigger = 1;
            new_datab->id = mx_strdup(argv[0]);
        }
        return 1;
    }
    return 0;
}

json_object *mx_if_logging(json_object *jobj, sqlite3 *db, t_datab *datab) {
    json_object *j_result = json_object_new_object();
    char sql[255];

    mx_js_to_datab(jobj, datab);
    sprintf(sql, "select ID, LOGIN, PASSWORD from USERS;");
    mx_table_setting(db, sql, cb_loganswer, datab);
    if (datab->logtrigger == 1 && datab->passtrigger == 1) {
        mx_user_activate(db, datab, datab->socket);
        mx_add_str_to_js(j_result, "Answer", MX_LOG_MES);
        mx_add_str_to_js(j_result, "Security_key", datab->security_key);
        mx_js_chts_conts_for_sender(j_result, db, datab, sql);
    }
    else
        mx_add_str_to_js(j_result, "Answer", MX_LOG_ERR);
    datab->logtrigger = 0;
    datab->passtrigger = 0;
    mx_strdel(&datab->id);
    mx_strdel(&datab->security_key);
    return j_result;
}
