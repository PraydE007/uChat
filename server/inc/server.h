#ifndef SERVER_H
#define SERVER_H

#include "../../inc/general.h"
#include <signal.h>
#include <strings.h>
#include "../../json/include/json-c/json.h"
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

typedef struct s_sockbd {
    int n;
    int sockfd;
    int log_sescr;
    const char *login;
    sqlite3 *bd;
    pthread_mutex_t mutex;
} t_sockbd;

typedef struct s_buf_do_proc {
    json_object *jobj;
    json_object *j_result;
    json_object *j_socket;
} t_buf_do_proc;

void *mx_doprocessing(void *data);
int mx_init_connect();
char *mx_hash_to_string(unsigned char *hash);
char *mx_hash(char *pass);
int mx_create_log();
void mx_demonize();
void mx_send_image_from_server(const char *file, int sockfd, int size);
t_buf_do_proc mx_handle_one(t_buf_do_proc buf_do_proc, t_sockbd sockbd);

#endif
