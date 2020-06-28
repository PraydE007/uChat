#include "dbase.h"

void mx_status_change(sqlite3 *db, char *login, int socket, int status) {
    int connection_point;
    char sql[255];

    printf("login: %s\n", login);
    if (status == 1) {
        sprintf(sql, "update USERS set SOCKET = %d, STATUS = 'active' " \
                "where LOGIN = '%s'", socket, login);
    }
    else if (status == 0) {
        sprintf(sql, "update USERS set SOCKET = -1, STATUS = 'passive' " \
                "where LOGIN = '%s'", login);
    }
    connection_point = sqlite3_exec(db, sql, mx_callback, NULL, NULL);
    if (connection_point != SQLITE_OK)
        fprintf(stderr, "error: %s\n", sqlite3_errmsg(db));
}
