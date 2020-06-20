#ifndef CLIENT_H
#define CLIENT_H

#include "../../inc/general.h"
#include <signal.h>
#include <pthread.h>

// typedef struct s_sock{
//     int test;
// } t_sock;

void *mx_doprocessing(void *data);
int mx_init_connect();


#endif
