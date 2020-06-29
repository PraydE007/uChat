#include "dbase.h"

static int cb_chatanswer(void *datab, int argc, char **argv, char **azColName) {
    (void)argc;
    (void)azColName;
    if (datab) {
        t_datab *new_datab = (t_datab *)datab;

        if (!mx_strcmp(new_datab->login_db, argv[1])) {
            new_datab->logtrigger = 1;
            return 1;
        }
    }
    return 0;
}

static void insert_chat(json_object *jobj, json_object *j_reslt, sqlite3 *db) {
    int connection_point;
    char sql[255];

    sprintf(sql, "insert into CHATS (CHAT_NAME, CHAT_STATUS)" \
            "values('%s', '%s')", mx_json_to_str(jobj, "Name"),
            mx_json_to_str(jobj, "Status"));
    connection_point = sqlite3_exec(db, sql, mx_callback, NULL, NULL);
    if (connection_point != SQLITE_OK)
        fprintf(stderr, "error: %s\n", sqlite3_errmsg(db));
    mx_js_add(j_reslt, "Answer", MX_CHAT_MES);
}

json_object *mx_if_chat(json_object *jobj, sqlite3 *db, t_datab *datab) {
    json_object *j_result = json_object_new_object();
    int connection_point;
    char sql[30];

    datab->login_db = mx_json_to_str(jobj, "Chat");
    sprintf(sql, "select ID, CHAT_NAME from CHATS;");
    connection_point = sqlite3_exec(db, sql, cb_chatanswer, datab, NULL);
    if (connection_point != SQLITE_OK && connection_point != SQLITE_ABORT)
        fprintf(stderr, "error: %s\n", sqlite3_errmsg(db));
    if (datab->logtrigger == 1)
        mx_js_add(j_result, "Answer", MX_CHAT_ERR);
    else
        insert_chat(jobj, j_result, db);
    printf("answer: %s\n", mx_json_to_str(j_result, "Answer")); //
    datab->logtrigger = 0;
    return j_result;
}
