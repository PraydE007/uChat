#ifndef DBASE_H
#define DBASE_H

#include "../../inc/general.h"
#include <sqlite3.h>

typedef struct s_datab {
    int logtrigger;
    int passtrigger;
    int socket;
    char *id;
    char *second_id;
    char *chat_id;
    char *chat_name;
    char *email;
    char *mobile;
    char *commd;
    char *type;
    char *security_key;
    const char *id_db;
    const char *login_db;
    const char *login_db2;
    const char *email_db;
    const char *mobile_db;
    const char *password_db;
    const char *security_db;
    const char *message_db;
    struct sqlite3 *db;
    struct json_object *j_result;
}               t_datab;

bool mx_is_active(json_object *jobj, sqlite3 *db, t_datab *datab);
bool mx_is_chat(sqlite3 *db, char *sql, t_datab *datab);
bool mx_check_login_on_server(sqlite3 *db, t_datab *datab, const char *login);
char *mx_find_user_login(sqlite3 *db, char *id);
char *mx_strjoin_free_js_value(char *s1, const char *s2);
const char *mx_js_arr_to_str(json_object *jobj, int index);
const char *mx_js_to_str(json_object *jobj, char *key);
int mx_callback(void *datab, int argc, char **argv, char **azColName);
int mx_cb_chat_id_finder(void *datab, int argc, char **argv, char **azColName);
int mx_js_to_int(json_object *jobj, char *key);
json_object *mx_dbase_handler(json_object *jobj, sqlite3 *db);
json_object *mx_if_change_passwd(json_object *jobj, sqlite3 *db, t_datab *datab);
json_object *mx_if_change_profile(json_object *jobj, sqlite3 *db, t_datab *datab);
json_object *mx_if_contact(json_object *jobj, sqlite3 *db, t_datab *datab);
json_object *mx_if_create_chat(json_object *jobj, sqlite3 *db, t_datab *datab);
json_object *mx_if_get_profile(json_object *jobj, sqlite3 *db, t_datab *datab);
json_object *mx_if_logging(json_object *jobj, sqlite3 *db, t_datab *datab);
json_object *mx_if_private_chat(json_object *jobj, sqlite3 *db, t_datab *datab);
json_object *mx_if_public_chat(json_object *jobj, sqlite3 *db, t_datab *datab);
json_object *mx_if_registr(json_object *jobj, sqlite3 *db, t_datab *datab);
json_object *mx_if_send_message(json_object *jobj, sqlite3 *db, t_datab *datab);
t_datab *mx_create_datab_node(void);
void mx_add_str_to_js(struct json_object *j_result, char *key, char *value);
void mx_add_arr_to_js(struct json_object *j_result, struct json_object *j_answer);
void mx_data_base_creation(sqlite3 **db);
void mx_dealloc_datab(t_datab **datab);
void mx_find_chat_name(sqlite3 *db, t_datab *datab, char *sql);
void mx_js_to_datab(json_object *jobj, t_datab *datab);
void mx_table_activity(sqlite3 *db, char *sql);
void mx_table_chats(sqlite3 *db, char *sql);
void mx_table_contacts(sqlite3 *db, char *sql);
void mx_table_creation(sqlite3 *db, char *sql, int (*callback)(void*, int, char**, char**));
void mx_table_messages(sqlite3 *db, char *sql);
void mx_table_setting(sqlite3 *db, char *sql, int (*callback)(void*, int, char**, char**), void *datab);
void mx_table_users(sqlite3 *db, char *sql);
void mx_table_users_chats(sqlite3 *db, char *sql);
void mx_trigger_for_activity(sqlite3 *db, char *sql);
void mx_trigger_for_messages_delete(sqlite3 *db, char *sql);
void mx_trigger_for_users(sqlite3 *db, char *sql);
void mx_user_activate(sqlite3 *db, t_datab *datab, int socket);
void mx_user_deactivate(sqlite3 *db, int socket);


#endif
