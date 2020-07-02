#include "dbase.h"

static int cb_id_finder(void *datab, int argc, char **argv, char **azColName) {
    (void)argc;
    (void)azColName;
    if (datab) {
        t_datab *new_datab = (t_datab *)datab;

        if (!mx_strcmp(new_datab->login_db2, argv[1])) {
            new_datab->second_id = mx_strdup(argv[0]);
            new_datab->logtrigger = 1;
            return 1;
        }
    }
    return 0;
}

static int cb_contact_id_finder(void *datab, int argc, char **argv,
                                                            char **azColName) {
    (void)argc;
    (void)azColName;
    if (datab) {
        t_datab *new_datab = (t_datab *)datab;

        if (!mx_strcmp(new_datab->second_id, argv[1])) {
            new_datab->passtrigger = 1;
            return 1;
        }
    }
    return 0;
}

static void insert_contact(json_object *j_result, sqlite3 *db, char *sql,
                                                            t_datab *datab) {
    int connection_point;
// printf("datab->id: %s\n", datab->id);
// printf("datab->second_id: %s\n", datab->second_id);
    sprintf(sql, "insert into CONTACTS (OWNER_id, FOLLOWER_id) " \
            "values(%s, %s)", datab->id, datab->second_id);
    connection_point = sqlite3_exec(db, sql, mx_callback, NULL, NULL);
    if (connection_point != SQLITE_OK && connection_point != SQLITE_ABORT)
        fprintf(stderr, "error: %s\n", sqlite3_errmsg(db));
    mx_js_add(j_result, "Answer", MX_CONT_MES);
    mx_strdel(&datab->id);
    mx_strdel(&datab->second_id);
}

// void condition_for_contact(json_object *j_result, sqlite3 *db, t_datab *datab,
//                                                                    char *sql) {
//     sprintf(sql, "select ID, LOGIN from USERS;");
//     mx_table_setting(db, sql, cb_id_finder, datab);
//     sprintf(sql, "select OWNER_id, FOLLOWER_id from CONTACTS " \
//             "where OWNER_id = %s;", datab->id);
//     printf("sql!!!: %s\n", sql);//
//     mx_table_setting(db, sql, cb_contact_id_finder, datab);
//     if (!mx_strcmp(datab->login_db, datab->login_db2))
//         mx_js_add(j_result, "Answer", "You can not add yourself into contacts!");
//     else if (datab->passtrigger == 1)
//         mx_js_add(j_result, "Answer", "You have already this contact in the list!");
//     else if (datab->logtrigger == 1)
//         insert_contact(j_result, db, sql, datab);
//     else
//         mx_js_add(j_result, "Answer", MX_CONT_ERR);
// }

json_object *mx_if_contact(json_object *jobj, sqlite3 *db, t_datab *datab) {
    json_object *j_result = json_object_new_object();
    char sql[255];

    datab->login_db2 = mx_json_to_str(jobj, "Contact_login");
    datab->security_db = mx_json_to_str(jobj, "Security_key");
    if (mx_is_active(jobj, db, datab)) {
        // condition_for_contact(j_result, db, datab, sql);
        sprintf(sql, "select ID, LOGIN from USERS;");
        mx_table_setting(db, sql, cb_id_finder, datab);
        sprintf(sql, "select OWNER_id, FOLLOWER_id from CONTACTS where OWNER_id = %s;", datab->id);
        printf("sql!!!: %s\n", sql);
        mx_table_setting(db, sql, cb_contact_id_finder, datab);
        if (!mx_strcmp(datab->login_db, datab->login_db2))
            mx_js_add(j_result, "Answer", "You can not add yourself into contacts!");
        else if (datab->passtrigger == 1)
            mx_js_add(j_result, "Answer", "You have already this contact in the list!");
        else if (datab->logtrigger == 1)
            insert_contact(j_result, db, sql, datab);
        else
            mx_js_add(j_result, "Answer", MX_CONT_ERR);
    }
    else
        mx_js_add(j_result, "Answer", MX_CHEAT_MESSAGE);
    mx_strdel(&datab->id);// comment in mx_is_active
    mx_strdel(&datab->second_id);
    datab->logtrigger = 0;
    datab->passtrigger = 0;
    return j_result;
}
