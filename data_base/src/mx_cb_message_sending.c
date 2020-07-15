#include "dbase.h"

int mx_cb_message_sending(void *datab, int argc, char **argv,
                                                            char **azColName) {
    (void)argc;
    (void)azColName;
    if (datab) {
        t_datab *new_datab = (t_datab *)datab;
        int n;

        n = send(mx_atoi(argv[0]), new_datab->message_db,
                                        mx_strlen(new_datab->message_db), 0);
    }
    return 0;
}
