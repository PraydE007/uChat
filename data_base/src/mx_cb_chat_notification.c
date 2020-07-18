#include "dbase.h"

int mx_cb_chat_notification(void *datab, int argc, char **argv,
                                                            char **azColName) {
    (void)argc;
    (void)azColName;
    if (datab) {
        t_datab *new_datab = (t_datab *)datab;
        int n;
        json_object *receive_notification = json_object_new_object();

        mx_add_str_to_js(receive_notification, "Answer",
                                                (char *)new_datab->message_db);
        mx_add_str_to_js(receive_notification, "Chat_name",
                                            (char *)new_datab->chat_name_db);
        mx_add_str_to_js(receive_notification, "Inviter",
                                                (char *)new_datab->login_db);
        new_datab->message_db = json_object_get_string(receive_notification);
        n = send(mx_atoi(argv[0]), new_datab->message_db,
                                        mx_strlen(new_datab->message_db),  0);
printf("new_datab->message_db: %s\n", new_datab->message_db);//
    }
    return 0;
}
