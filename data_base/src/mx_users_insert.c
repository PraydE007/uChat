#include "dbase.h"

void mx_users_insert(json_object *jobj, sqlite3 *db) {
    int connection_point;
    char sql[255];

    sprintf(sql, "insert into USERS (LOGIN, PASSWORD, EMAIL)" \
            "values('%s', '%s', '%s')", mx_json_to_str(jobj, "Login"),
            mx_json_to_str(jobj, "Passwd"), mx_json_to_str(jobj, "Email"));
    connection_point = sqlite3_exec(db, sql, mx_callback, NULL, NULL);
    if (connection_point != SQLITE_OK)
        fprintf(stderr, "error: %s\n", sqlite3_errmsg(db));
}
