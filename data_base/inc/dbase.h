#ifndef DBASE_H
#define DBASE_H

#include "../inc/general.h"
#include <signal.h>
#include <pthread.h>

// typedef struct s_sock{
//     int test;
// } t_sock;

void *doprocessing(void *sock);



#endif