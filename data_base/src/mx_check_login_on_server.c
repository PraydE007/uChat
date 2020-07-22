#include "dbase.h"

static int cb_login_checking(void *datab, int argc, char **argv,
                             char **azColName) {
    (void)argc;
    (void)azColName;
    if (datab) {
        t_datab *new_datab = (t_datab *)datab;
        if (!mx_strcmp(new_datab->login_db2, argv[0])) {
            new_datab->logtrigger = 1;
            return 1;
        }
    }
    return 0;
}

bool mx_check_login_on_server(sqlite3 *db, t_datab *datab, const char *login) {
    bool result = false;
    char sql[30];

    datab->login_db2 = login;
    sprintf(sql, "select LOGIN from USERS;");
    mx_table_setting(db, sql, cb_login_checking, datab);
    if (datab->logtrigger == 1) {
        datab->logtrigger = 0;
        result = true;
    }
    return result;
}
