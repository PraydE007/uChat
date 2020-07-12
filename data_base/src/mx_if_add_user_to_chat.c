#include "dbase.h"

// static int cb_id_finder(void *datab, int argc, char **argv, char **azColName) {
//     (void)argc;
//     (void)azColName;
//     if (datab) {
//         t_datab *new_datab = (t_datab *)datab;

//         if (!mx_strcmp(new_datab->login_db2, argv[1])) {
//             new_datab->second_id = mx_strdup(argv[0]);
//             new_datab->logtrigger = 1;
//             return 1;
//         }
//     }
//     return 0;
// }

static int cb_find_chat_id_and_status(void *datab, int argc, char **argv,
                                                            char **azColName) {
    (void)argc;
    (void)azColName;
    if (datab) {
        t_datab *new_datab = (t_datab *)datab;

printf("argv[0]: %s\n", argv[0]);
printf("argv[1]: %s\n", argv[1]);
        new_datab->chat_id = mx_strdup(argv[0]);
        new_datab->chat_status = mx_strdup(argv[1]);
printf("new_datab->chat_id: %s\n", new_datab->chat_id);
printf("new_datab->chat_status: %s\n", new_datab->chat_status);
    }
    return 0;
}

static int cb_find_contact_id_in_chat(void *datab, int argc, char **argv,
                                                            char **azColName) {
    (void)argc;
    (void)azColName;
    if (datab) {
        t_datab *new_datab = (t_datab *)datab;

        if (!mx_strcmp(new_datab->second_id, argv[1])) {
            new_datab->passtrigger = 1;
            return 1;
        }
    }
    return 0;
}

// static int chat_notification(void *datab, int argc, char **argv,
//                                                             char **azColName) {
//     (void)argc;
//     (void)azColName;
//     if (datab) {
//         t_datab *new_datab = (t_datab *)datab;
//         int n;
//         json_object *receive_notification = json_object_new_object();
//         mx_add_str_to_js(receive_notification, "Answer", "You were added to the chat");
//         mx_add_str_to_js(receive_notification, "Chat_name",
//                                                 (char *)new_datab->chat_name_db);
//         mx_add_str_to_js(receive_notification, "Inviter",
//                                                 (char *)new_datab->login_db);
//         new_datab->message_db = json_object_get_string(receive_notification);
//         n = send(mx_atoi(argv[0]), new_datab->message_db,
//                                         mx_strlen(new_datab->message_db),  0);
//         printf("new_datab->message_db: %s\n", new_datab->message_db);//
//     }
//     return 0;
// }

static void insert_contact_in_to_chat(json_object *j_result, sqlite3 *db,
                                                char *sql, t_datab *datab) {
    sprintf(sql, "insert into USERS_CHATS (USER_id, CHAT_id)" \
            "values('%s', '%s')", datab->second_id, datab->chat_id);
    mx_table_creation(db, sql, mx_callback);
    mx_add_str_to_js(j_result, "Answer", MX_CONT_ADD_CHAT);
    sprintf(sql, "select SOCKET from ACTIVITY where USER_id = '%s';",
                                                            datab->second_id);
        mx_table_setting(db, sql, mx_cb_chat_notification, datab);
    mx_strdel(&datab->second_id);
}

void condition_for_chat(json_object *j_result, sqlite3 *db, t_datab *datab,
                                                                   char *sql) {
    sprintf(sql, "select ID, LOGIN from USERS;");
    mx_table_setting(db, sql, mx_cb_find_user_id, datab);
    if (datab->second_id) {
        sprintf(sql, "select USER_id, CHAT_id from USERS_CHATS " \
                "where CHAT_id = %s;", datab->chat_id);
        mx_table_setting(db, sql, cb_find_contact_id_in_chat, datab);
        if (!mx_strcmp(datab->login_db, datab->login_db2))
            mx_add_str_to_js(j_result, "Answer", "You can not add yourself " \
                        "into chat!");
        else if (datab->passtrigger == 1)
            mx_add_str_to_js(j_result, "Answer", "You have already this contact " \
                        "in the chat!");
        else if (datab->logtrigger == 1)
            insert_contact_in_to_chat(j_result, db, sql, datab);
    }
    else
        mx_add_str_to_js(j_result, "Answer", MX_CONT_ERR);
    mx_strdel(&datab->chat_id);
    datab->logtrigger = 0;
    datab->passtrigger = 0;
}

json_object *mx_if_add_user_to_chat(json_object *jobj, sqlite3 *db,
                                                            t_datab *datab) {
    json_object *j_result = json_object_new_object();
    char sql[255];

    if (mx_is_active(jobj, db, datab)) {
printf("1\n");
        datab->login_db2 = mx_js_to_str(jobj, "Contact_login");
        datab->chat_name_db = mx_js_to_str(jobj, "Chat_name");
printf("datab->chat_name_db1: %s\n", datab->chat_name_db);
        sprintf(sql, "select ID, CHAT_STATUS from CHATS " \
                "where CHAT_NAME = '%s';", datab->chat_name_db);
        mx_table_setting(db, sql, cb_find_chat_id_and_status, datab);
printf("3\n");
printf("datab->chat_name_db2: %s\n", datab->chat_name_db);
printf("datab->chat_status: %s\n", datab->chat_status);
        if (!mx_strcmp(datab->chat_status, "public")) {
printf("4\n");
            condition_for_chat(j_result, db, datab, sql);
        }
        else {
printf("5\n");
            mx_add_str_to_js(j_result, "Answer", MX_PRIVATE_CHAT);
        }
    }
    else
        mx_add_str_to_js(j_result, "Answer", MX_CHEAT_MESSAGE);
printf("if_add_contact(j_result): %s\n", json_object_to_json_string(j_result));//
    mx_strdel(&datab->id);// comment in mx_is_active
    mx_strdel(&datab->chat_status);
    return j_result;
}
