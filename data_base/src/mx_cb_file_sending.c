#include "dbase.h"
//CHECK IF WE NEED THIS FILE
int mx_cb_file_sending(void *datab, int argc, char **argv, char **azColName) {
    (void)argc;
    (void)azColName;
    if (datab) {
        t_datab *new_datab = (t_datab *)datab;
printf("fpath_db = %s\n", new_datab->fpath_db);
        mx_send_image_from_server(new_datab->fpath_db, mx_atoi(argv[0]), mx_atoi(new_datab->fsize_db));
    }
    return 0;
}
