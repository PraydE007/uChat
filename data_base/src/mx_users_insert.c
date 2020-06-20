#include "dbase.h"

static int callback(void *datab, int argc, char **argv, char **azColName) {
    (void)datab;
    (void)argc;
    (void)argv;
    (void)azColName;
    return 0;
}

void mx_users_insert(json_object *jobj, sqlite3 *db) {
    int connection_point;
    char *err = NULL;
    char sql[255];

    sprintf(sql, "insert into USERS (LOGIN, PASSWORD, EMAIL)" \
            "values('%s', '%s', '%s')", mx_json_to_str(jobj, "Login"), 
            mx_json_to_str(jobj, "Passwd"), mx_json_to_str(jobj, "Email"));
    connection_point = sqlite3_exec(db, sql, callback, NULL, &err);
    if (err != SQLITE_OK)
        fprintf(stderr, "error: %s\n", sqlite3_errmsg(db));
}
