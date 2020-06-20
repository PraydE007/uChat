#ifndef DBASE_H
#define DBASE_H

#include "../../inc/general.h"
#include <sqlite3.h>

typedef struct s_datab {
    int logtrigger;
    int passtrigger;
    const char *login_db;
    const char *password_db;
}               t_datab;

const char *mx_json_to_str(json_object *jobj, char *key);
json_object *mx_dbase_handler(json_object *jobj, sqlite3 *db);
json_object *mx_if_logging(json_object *jobj, sqlite3 *db, t_datab *datab);
json_object *mx_if_registr(json_object *jobj, sqlite3 *db, t_datab *datab);
t_datab *mx_create_datab_node(void);
void mx_data_base_creation(sqlite3 **db);
void mx_js_add(json_object *j_result, char *key, char *value);
void mx_users_insert(json_object *jobj, sqlite3 *db);


#endif
