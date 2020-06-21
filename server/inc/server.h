#ifndef CLIENT_H
#define CLIENT_H

#include "../../inc/general.h"
#include <signal.h>
#include <pthread.h>
#include "../../json/include/json-c/json.h"
#include <stdio.h>
// typedef struct s_sock{
//     int test;
// } t_sock;

void *doprocessing(void *sock);
int mx_init_connect();
char *mx_hash_to_string(unsigned char *hash);
char *mx_hash(char *pass);

#endif
