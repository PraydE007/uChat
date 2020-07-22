#include "dbase.h"

static int cb_login_finder(void *login, int argc, char **argv,
                           char **azColName) {
    (void)argc;
    (void)azColName;

    char **new_login = (char **)(login);
    *new_login = mx_strdup(argv[0]);
    return 0;
}

char *mx_find_user_login(sqlite3 *db, char *id) {
    char *login = NULL;
    char sql[255];

    sprintf(sql, "select LOGIN from USERS where ID = '%s';", id);
    mx_table_setting(db, sql, cb_login_finder, &login);
    return login;
}
