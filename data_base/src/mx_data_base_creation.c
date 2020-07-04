#include "dbase.h"

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    int i;
    (*(int*)NotUsed)++;
    // (*(int*)NotUsed)++;
    // (*(int*)NotUsed)--;
    for(i = 0; i<argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

void mx_data_base_creation(sqlite3 **db) {
    int connection_point;
    char sql[512];
    int i = 0;
    int * p = &i;

    connection_point = sqlite3_open("chat_base.db", db);
    if(connection_point)
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(*db));
    else
        fprintf(stdout, "Opened database successfully\n");
    sprintf(sql, "DROP TABLE IF EXISTS ACTIVITY;");
    connection_point = sqlite3_exec(*db, sql, callback, p, NULL);
    mx_table_users(*db, sql);
    mx_table_chats(*db, sql);
    mx_table_users_chats(*db, sql);
    mx_table_messages(*db, sql);
    mx_table_contacts(*db, sql);
    mx_table_activity(*db, sql);
    mx_trigger_for_activity(*db, sql);
    mx_trigger_for_users(*db, sql);
    mx_trigger_for_messages_delete(*db, sql);
    // sprintf(sql, "CREATE TABLE IF NOT EXISTS 'USERS'(" \
    //     "ID INTEGER PRIMARY KEY AUTOINCREMENT," \
    //     "LOGIN          VARCHAR(50)     NOT NULL," \
    //     "PASSWORD       VARCHAR(50)     NOT NULL," \
    //     "EMAIL          VARCHAR(50)     NOT NULL);");
    // connection_point = sqlite3_exec(*db, sql, callback, 0, &err);
    // if (err != SQLITE_OK)
    //     fprintf(stderr, "error: %s\n", sqlite3_errmsg(*db));
    // sprintf(sql, "CREATE TABLE IF NOT EXISTS 'CHATS'(" \
    //     "ID INTEGER PRIMARY KEY AUTOINCREMENT);");
    // sprintf(sql, "CREATE TABLE IF NOT EXISTS 'USERS_CHATS'(" \
    //     "USER_id INTEGER NOT NULL," \
    //     "CHAT_id INTEGER NOT NULL;");
    // sprintf(sql, "CREATE TABLE IF NOT EXISTS 'MESSAGES'(" \
    //     "ID INTEGER PRIMARY KEY AUTOINCREMENT," \
    //     "SENDER_id INTEGER NOT NULL," \
    //     "CHAT_id INTEGER NOT NULL;");
    // CREATE TRIGGER IF NOT EXISTS insertion AFTER INSERT
    // ON CHATS
    // BEGIN
    // INSERT INTO USERS_CHATS(id_u, u_date) VALUES (NEW.id, datetime('now'));
    // END;
    // connection_point = sqlite3_exec(*db, sql, callback, 0, &err);

    // sprintf(sql, "insert into USERS (LOGIN, PASSWORD, EMAIL) values('Vova', 'tyuri45637', 'vova@gmail.com')");
    // connection_point = sqlite3_exec(*db, sql, callback, 0, &err);
    // if (err != SQLITE_OK) {
    //     fprintf(stderr, "error: %s\n", sqlite3_errmsg(*db));
    // }
    // sprintf(sql, "insert into CHATS (CHAT_NAME, CHAT_STATUS) values('The best', 'private')");
    // connection_point = sqlite3_exec(*db, sql, callback, 0, NULL);
    // sprintf(sql, "insert into CHATS (CHAT_NAME, CHAT_STATUS) values('Chisto potrindetb', 'public')");
    // connection_point = sqlite3_exec(*db, sql, callback, 0, NULL);
    // sprintf(sql, "insert into CHATS (CHAT_NAME, CHAT_STATUS) values('Tryndelki', 'public')");
    // connection_point = sqlite3_exec(*db, sql, callback, 0, NULL);
    // sprintf(sql, "insert into USERS_CHATS (USER_id, CHAT_id) values('1', '1')");
    // connection_point = sqlite3_exec(*db, sql, callback, 0, NULL);
    // sprintf(sql, "insert into USERS_CHATS (USER_id, CHAT_id) values('1', '2')");
    // connection_point = sqlite3_exec(*db, sql, callback, 0, NULL);
    // sprintf(sql, "insert into USERS_CHATS (USER_id, CHAT_id) values('1', '3')");
    // connection_point = sqlite3_exec(*db, sql, callback, 0, NULL);
    // sprintf(sql, "insert into USERS_CHATS (USER_id, CHAT_id) values('2', '2')");
    // connection_point = sqlite3_exec(*db, sql, callback, 0, NULL);
    // sprintf(sql, "insert into USERS_CHATS (USER_id, CHAT_id) values('2', '4')");
    // connection_point = sqlite3_exec(*db, sql, callback, 0, NULL);
    // sprintf(sql, "insert into USERS_CHATS (USER_id, CHAT_id) values('2', '5')");
    // connection_point = sqlite3_exec(*db, sql, callback, 0, NULL);
    // sprintf(sql, "insert into USERS_CHATS (USER_id, CHAT_id) values('3', '1')");
    // connection_point = sqlite3_exec(*db, sql, callback, 0, NULL);
    // sprintf(sql, "insert into USERS_CHATS (USER_id, CHAT_id) values('3', '2')");
    // connection_point = sqlite3_exec(*db, sql, callback, 0, NULL);
    // sprintf(sql, "insert into USERS_CHATS (USER_id, CHAT_id) values('4', '2')");
    // connection_point = sqlite3_exec(*db, sql, callback, 0, NULL);
    // sprintf(sql, "insert into CONTACTS (OWNER_id, FOLLOWER_id) values('1', '5')");
    // connection_point = sqlite3_exec(*db, sql, callback, 0, NULL);
    // sprintf(sql, "insert into CONTACTS (OWNER_id, FOLLOWER_id) values('1', '4')");
    // connection_point = sqlite3_exec(*db, sql, callback, 0, NULL);
    // sprintf(sql, "insert into CONTACTS (OWNER_id, FOLLOWER_id) values('1', '2')");
    // connection_point = sqlite3_exec(*db, sql, callback, 0, NULL);
    // sprintf(sql, "insert into CONTACTS (OWNER_id, FOLLOWER_id) values('1', '3')");
    // connection_point = sqlite3_exec(*db, sql, callback, 0, NULL);
    // sprintf(sql, "insert into MESSAGES (SENDER_id, CHAT_id, MESSAGE_text) values(1, 2, 'YO, kak dela, Bill?')");
    // connection_point = sqlite3_exec(*db, sql, callback, 0, NULL);
    // sprintf(sql, "insert into MESSAGES (SENDER_id, CHAT_id, MESSAGE_text) values(2, 2, 'I am still waiting for you')");
    // connection_point = sqlite3_exec(*db, sql, callback, 0, NULL);
    // sprintf(sql, "insert into MESSAGES (SENDER_id, CHAT_id, MESSAGE_text) values(1, 2, 'Where are you?')");
    // connection_point = sqlite3_exec(*db, sql, callback, 0, NULL);
    // if (connection_point != SQLITE_OK) {
    //     fprintf(stderr, "error: %s\n", sqlite3_errmsg(*db));
    // }
    // char id[3] = "1\0";
    // sprintf(sql, "select * from USERS WHERE ID >= %s AND ID < '30';", id);
    // connection_point = sqlite3_exec(*db, sql, callback, p, NULL);
    // printf("count  = %d\n", i);
    // sprintf(sql, "DROP TABLE IF EXISTS CONTACTS;");
    // connection_point = sqlite3_exec(*db, sql, callback, p, NULL);
    // sprintf(sql, "DELETE FROM USERS WHERE ID = 1;");
    // connection_point = sqlite3_exec(*db, sql, callback, p, NULL);
    // sprintf(sql, "DELETE FROM USERS WHERE ID = 2;");
    // connection_point = sqlite3_exec(*db, sql, callback, p, NULL);
    // sprintf(sql, "DELETE FROM CHATS WHERE CHAT_NAME = 'The best';");
    // connection_point = sqlite3_exec(*db, sql, callback, p, NULL);
    // sprintf(sql, "DELETE FROM CHATS WHERE ID = 2;");
    // connection_point = sqlite3_exec(*db, sql, callback, p, NULL);
    // printf("sql  = %s\n", sql);
    // if(connection_point != SQLITE_OK){
    //     fprintf(stderr, "SQL error: %s\n", err);
    //     sqlite3_free(err);
    // }
    // else
    //     fprintf(stdout, "Table created successfully\n");
    // sqlite3_close(db);
}
