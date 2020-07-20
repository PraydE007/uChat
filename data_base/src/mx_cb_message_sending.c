#include "dbase.h"

int mx_cb_message_sending(void *datab, int argc, char **argv,
                                                            char **azColName) {
    (void)argc;
    (void)azColName;
    if (datab) {
        t_datab *new_datab = (t_datab *)datab;
        int n;

        n = send(mx_atoi(argv[0]), new_datab->message_db,
                                        MX_MAX_BYTES, 0);
        if (new_datab->fpath_db)
            mx_send_image_from_server(new_datab->fpath_db, mx_atoi(argv[0]), mx_atoi(new_datab->fsize_db));
        printf("fpath_db = %s\n", new_datab->fpath_db);
    }
    return 0;
}
