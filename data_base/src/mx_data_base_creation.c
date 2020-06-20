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

static void table_creator(sqlite3 *db, char *sql) {
    char *err = NULL;
    int connection_point;

    connection_point = sqlite3_exec(db, sql, callback, 0, &err);
    if (err != SQLITE_OK)
        fprintf(stderr, "error: %s\n", sqlite3_errmsg(db));
}

void mx_data_base_creation(sqlite3 **db) {
    char *err = NULL;
    int connection_point;
    char sql[1024];
    int i = 0;
    int * p = &i;

    connection_point = sqlite3_open("chat_base.db", db);
    if(connection_point)
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(*db));
    else
        fprintf(stdout, "Opened database successfully\n");
    mx_table_users(sql);
    table_creator(*db, sql);
    mx_table_chats(sql);
    table_creator(*db, sql);
    mx_table_users_chats(sql);
    table_creator(*db, sql);
    mx_table_messages(sql);
    table_creator(*db, sql);
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
    char id[3] = "1\0";
    sprintf(sql, "select * from USERS WHERE ID >= %s AND ID < '30';", id);
    connection_point = sqlite3_exec(*db, sql, callback, p, &err);
    printf("count  = %d\n", i);
    // if(connection_point != SQLITE_OK){
    //     fprintf(stderr, "SQL error: %s\n", err);
    //     sqlite3_free(err);
    // }
    // else
    //     fprintf(stdout, "Table created successfully\n");
    // sqlite3_close(db);
}
