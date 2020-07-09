#include "dbase.h"

int mx_cb_find_user_id(void *datab, int argc, char **argv, char **azColName) {
    (void)argc;
    (void)azColName;
    if (datab) {
        t_datab *new_datab = (t_datab *)datab;

        if (!mx_strcmp(new_datab->login_db2, argv[1])) {
            new_datab->second_id = mx_strdup(argv[0]);
            new_datab->logtrigger = 1;
            return 1;
        }
    }
    return 0;
}
