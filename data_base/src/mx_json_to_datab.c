#include "dbase.h"

void mx_json_to_datab(json_object *jobj, t_datab *datab) {
    datab->login_db = mx_json_to_str(jobj, "Login");
    datab->password_db = mx_json_to_str(jobj, "Passwd");
    datab->socket = mx_json_to_int(jobj, "Socket");
    if(datab->socket % 2 == 0) {
        datab->security_key =
        mx_strjoin(MX_SECURITY_KEY, mx_itoa(datab->socket));
        datab->security_key =
        mx_strjoin_free(datab->security_key, datab->password_db);
    }
    else {
        datab->security_key = mx_strjoin(datab->password_db, MX_SECURITY_KEY);
        datab->security_key =
        mx_strjoin(datab->security_key, mx_itoa(datab->socket));
    }
}
