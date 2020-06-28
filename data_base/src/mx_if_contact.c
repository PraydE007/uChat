#include "dbase.h"

static int cb_conanswer(void *datab, int argc, char **argv, char **azColName) {
    (void)argc;
    (void)azColName;
    if (datab) {
        t_datab *new_datab = (t_datab *)datab;

        if (!mx_strcmp(new_datab->login_db, argv[0])) {
            new_datab->id = mx_strdup(argv[0]);
            new_datab->logtrigger = 1;
            if (new_datab->passtrigger == 1)
                return 1;
        }
        else if (!mx_strcmp(new_datab->login_db2, argv[1])) {
            new_datab->second_id = mx_strdup(argv[1]);
            new_datab->passtrigger = 1;
            if (new_datab->logtrigger == 1)
                return 1;
        }
    }
    return 0;
}

static void insert_contact(json_object *j_result, sqlite3 *db, char *sql) {
    int connection_point;

    sprintf(sql, "insert into CONTACTS (OWNER_id, FOLLOWER_id) " \
            "values(datab->id, datab->second_id)");
    connection_point = sqlite3_exec(db, sql, mx_callback, NULL, NULL);
    if (connection_point != SQLITE_OK && connection_point != SQLITE_ABORT)
        fprintf(stderr, "error: %s\n", sqlite3_errmsg(db));
    mx_js_add(j_result, "Answer", MX_CONT_MES);
}

json_object *mx_if_contact(json_object *jobj, sqlite3 *db, t_datab *datab) {
    json_object *j_result = json_object_new_object();
    int connection_point;
    char sql[255];

    datab->login_db = mx_json_to_str(jobj, "Login");
    datab->login_db2 = mx_json_to_str(jobj, "Contact_login");
    sprintf(sql, "select LOGIN from USERS;");
    connection_point = sqlite3_exec(db, sql, cb_conanswer, datab, NULL);
    if (connection_point != SQLITE_OK && connection_point != SQLITE_ABORT)
        fprintf(stderr, "error: %s\n", sqlite3_errmsg(db));
    if (datab->logtrigger == 1 && datab->passtrigger == 1)
        insert_contact(j_result, db, sql);
    else
        mx_js_add(j_result, "Answer", MX_CONT_ERR);
    printf("answer: %s\n", mx_json_to_str(j_result, "Answer"));//
    mx_strdel(&datab->id);
    mx_strdel(&datab->second_id);
    datab->logtrigger = 0;
    datab->passtrigger = 0;
    return j_result;
}
