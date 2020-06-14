// #include "dbase.h"
#include <sqlite3.h> 
#include <stdio.h>
#include <stdlib.h>

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

void mx_data_base_creation(void) {
    sqlite3 *db;
    char *err = NULL;
    int connection_point;
    char sql[200] ;
    int i = 0;
    int * p = &i;
    connection_point = sqlite3_open("chat_base.db", &db);
    if(connection_point)
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    else
        fprintf(stdout, "Opened database successfully\n");
    sprintf(sql, "CREATE TABLE IF NOT EXISTS 'GENERAL_TABLE'(" \
        "ID INTEGER PRIMARY KEY AUTOINCREMENT," \
        "NAME           VARCHAR(255)    NOT NULL," \
        "MOBILEPHONE    INT             NOT NULL);");
    connection_point = sqlite3_exec(db, sql, callback, 0, &err);

    sprintf(sql, "insert into GENERAL_TABLE values(NULL, 'Vasya', '98')");
    connection_point = sqlite3_exec(db, sql, callback, 0, &err);
    if (err != SQLITE_OK) {
        fprintf(stderr, "error: %s\n", sqlite3_errmsg(db));
    }
    char id[3] = "12\0";
    sprintf(sql, "select * from GENERAL_TABLE WHERE ID > %s AND ID < '30';", id);
    connection_point = sqlite3_exec(db, sql, callback, p, &err);
    printf("count  = %d\n", i);
    if(connection_point != SQLITE_OK){
        fprintf(stderr, "SQL error: %s\n", err);
        sqlite3_free(err);
    }
    else
        fprintf(stdout, "Table created successfully\n");

    sqlite3_close(db);
}

int main() {
    mx_data_base_creation();
    return 0;
}
