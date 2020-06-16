#include "dbase.h"

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    int i;
    (*(int*)NotUsed)++;
    // (*(int*)NotUsed)++;
    // (*(int*)NotUsed)--;
    for(i = 0; i<argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

json_object *mx_if_logging(json_object *parsed) {
    json_object *result = json_object_new_object();
    int connection_point;
    sqlite3 *db;
    char *err = NULL;
    char sql[50] ;
    struct json_object *logging;
    const char *all_data = NULL;

    connection_point = sqlite3_open("chat_base.db", &db);
    if(connection_point)
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    else
        fprintf(stdout, "Opened database successfully\n");
    sprintf(sql, "select * from GENERAL_TABLE WHERE ID > %s AND ID < '30';", id);
    json_object_object_get_ex(parsed, "Logging", &logging);
    connection_point = sqlite3_exec(db, sql, callback, p, &err);
    if (!mx_strcmp("\"Logging\"", json_object_to_json_string(type))) {
        // result = mx_if_logging(jobj);
        // printf("%s", json_object_to_json_string(name));
    }
    if (!mx_strcmp("\"Registration\"", json_object_to_json_string(type))) {
        // result = mx_if_logging(jobj);
    }
}
