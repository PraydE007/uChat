#include "dbase.h"

// static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
//     int i;
//     // (*(int*)NotUsed)++;
//     (*(int*)NotUsed)++;
//     (*(int*)NotUsed)--;
//     for(i = 0; i<argc; i++) {
//         printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
//     }
//     printf("\n");
//     return 0;
// }

json_object *mx_dbase_handler(json_object *jobj, sqlite3 *db) {
    t_datab *datab = mx_create_datab_node();
    json_object *j_result = json_object_new_object();

// char id[4] = "BBB\0";
// int connection_point;
// char sql[255];
// sprintf(sql, "DELETE FROM 'USERS' WHERE ID = %s;", id);
// connection_point = sqlite3_exec(db, sql, callback, 0, NULL);
// printf("sql  = %s\n", sql);
// sprintf(sql, "DELETE FROM USERS WHERE ID = 4;");
// connection_point = sqlite3_exec(db, sql, callback, 0, NULL);

    if (!mx_strcmp("Logging", mx_json_to_str(jobj, "Type")))
        j_result = mx_if_logging(jobj, db, datab);
    else if (!mx_strcmp("Registr", mx_json_to_str(jobj, "Type")))
        j_result = mx_if_registr(jobj, db, datab);
    return j_result;
}
