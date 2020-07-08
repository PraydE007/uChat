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
// A LOT OF LINES
static void insert_contact(json_object *j_result, sqlite3 *db, char *sql,
                                                            t_datab *datab) {
    sprintf(sql, "insert into CONTACTS (OWNER_id, FOLLOWER_id) " \
            "values(%s, %s)", datab->id, datab->second_id);
    mx_table_creation(db, sql, mx_callback);
    datab->chat_name = mx_strjoin(datab->login_db2, datab->login_db);
    if (!mx_is_chat(db, sql, datab)) {
        mx_strdel(&datab->chat_name);
        datab->chat_name = mx_strjoin(datab->login_db, datab->login_db2);
        sprintf(sql, "insert into CHATS (CHAT_NAME, CHAT_STATUS) " \
                "values('%s', '%s')", datab->chat_name, "private");
        mx_table_creation(db, sql, mx_callback);
        sprintf(sql, "select ID from CHATS where CHAT_NAME = '%s';",
                datab->chat_name);
        mx_table_setting(db, sql, mx_cb_chat_id_finder, datab);
        sprintf(sql, "insert into USERS_CHATS (USER_id, CHAT_id)" \
                "values('%s', '%s')", datab->id, datab->chat_id);
        mx_table_creation(db, sql, mx_callback);
        sprintf(sql, "insert into USERS_CHATS (USER_id, CHAT_id)" \
                "values('%s', '%s')", datab->second_id, datab->chat_id);
        mx_table_creation(db, sql, mx_callback);
    }
    mx_add_str_to_js(j_result, "Answer", MX_CONT_MES);
    mx_strdel(&datab->chat_name);
}

void condition_for_contact(json_object *j_result, sqlite3 *db, t_datab *datab,
                                                                   char *sql) {
    sprintf(sql, "select ID, LOGIN from USERS;");
    mx_table_setting(db, sql, cb_id_finder, datab);
    if (datab->second_id) {
            sprintf(sql, "select OWNER_id, FOLLOWER_id from CONTACTS " \
                    "where OWNER_id = %s;", datab->id);
            mx_table_setting(db, sql, cb_contact_id_finder, datab);
        }
    if (!mx_strcmp(datab->login_db, datab->login_db2))
        mx_add_str_to_js(j_result, "Answer", "You can not add yourself " \
                      "into contacts!");
    else if (datab->passtrigger == 1)
        mx_add_str_to_js(j_result, "Answer", "You have already this contact " \
                      "in the list!");
    else if (datab->logtrigger == 1)
        insert_contact(j_result, db, sql, datab);
    else
        mx_add_str_to_js(j_result, "Answer", MX_CONT_ERR);
}

json_object *mx_if_contact(json_object *jobj, sqlite3 *db, t_datab *datab) {
    json_object *j_result = json_object_new_object();
    char sql[255];

    datab->login_db2 = mx_js_to_str(jobj, "Contact_login");
    datab->security_db = mx_js_to_str(jobj, "Security_key");
    if (mx_is_active(jobj, db, datab))
        condition_for_contact(j_result, db, datab, sql);
    else
        mx_add_str_to_js(j_result, "Answer", MX_CHEAT_MESSAGE);
printf("if_contact(j_result): %s\n", json_object_to_json_string(j_result));//
    mx_strdel(&datab->id);// comment in mx_is_active
    mx_strdel(&datab->second_id);
    datab->logtrigger = 0;
    datab->passtrigger = 0;
    return j_result;
}
