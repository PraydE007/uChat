#include "dbase.h"

void mx_user_activate(sqlite3 *db, t_datab *datab, int socket) {
    int connection_point;
    char sql[255];

    sprintf(sql, "update USERS set SOCKET = %d, SECURITY_KEY = '%s' " \
           "where LOGIN = '%s'", socket, datab->security_key, datab->login_db);
    connection_point = sqlite3_exec(db, sql, mx_callback, NULL, NULL);
    if (connection_point != SQLITE_OK)
        fprintf(stderr, "error: %s\n", sqlite3_errmsg(db));
}
