#include "dbase.h"

int mx_cb_chat_notification(void *datab, int argc, char **argv,
                                                            char **azColName) {
    (void)argc;
    (void)azColName;
    if (datab) {
        t_datab *new_datab = (t_datab *)datab;
        json_object *rciv_not = json_object_new_object();
        char sql[255];
        int n;

        mx_add_str_to_js(rciv_not, "Answer",
                                                (char *)new_datab->message_db);
        mx_add_str_to_js(rciv_not, "Chat_name",
                                            (char *)new_datab->chat_name_db);
        mx_add_str_to_js(rciv_not, "Inviter",
                                                (char *)new_datab->login_db);
        mx_js_chts_conts_for_receiver(rciv_not, new_datab->db, new_datab, sql);
        new_datab->message_db = json_object_get_string(rciv_not);
        n = send(mx_atoi(argv[0]), new_datab->message_db,
                                        mx_strlen(new_datab->message_db),  0);
printf("new_datab->message_db!!!: %s\n", new_datab->message_db);//
    }
    return 0;
}
