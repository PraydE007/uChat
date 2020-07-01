#include "dbase.h"

void mx_user_deactivate(sqlite3 *db, int socket) {
    int connection_point;
    char sql[255];

    sprintf(sql, "delete from ACTIVITY where SOCKET = %d;", socket);
    connection_point = sqlite3_exec(db, sql, mx_callback, NULL, NULL);
    if (connection_point != SQLITE_OK)
        fprintf(stderr, "error: %s\n", sqlite3_errmsg(db));
}
