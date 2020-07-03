#include "dbase.h"

int mx_cb_chat_id_finder(void *datab, int argc, char **argv, char **azColName) {
    (void)argc;
    (void)azColName;
    if (datab) {
        t_datab *new_datab = (t_datab *)datab;

        new_datab->chat_id = mx_strdup(argv[0]);
    }
    return 0;
}
