#include "dbase.h"

static int cb_login_checking(void *datab, int argc, char **argv,
                                                            char **azColName) {
    (void)argc;
    (void)azColName;
    if (datab) {
        t_datab *new_datab = (t_datab *)datab;
printf("new_datab->login_db: %s\n", new_datab->login_db2); //
        if (!mx_strcmp(new_datab->login_db2, argv[0])) {
            new_datab->logtrigger = 1;
            return 1;
        }
    }
    return 0;
}

bool mx_check_login_on_server(sqlite3 *db, t_datab *datab, const char *login) {
    bool result = false;
    // int connection_point;
    char sql[30];

    datab->login_db2 = login;
    sprintf(sql, "select LOGIN from USERS;");
    mx_table_setting(db, sql, cb_login_checking, datab);
    // connection_point = sqlite3_exec(db, sql, cb_reganswer, datab, NULL);
    // if (connection_point != SQLITE_OK && connection_point != SQLITE_ABORT)
    //     fprintf(stderr, "error: %s\n", sqlite3_errmsg(db));
    if (datab->logtrigger == 1)
        result = true;
printf("answer: %d\n", result); //
    datab->logtrigger = 0;
    return result;
}
