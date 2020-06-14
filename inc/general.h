#ifndef GENERAL_H
#define GENERAL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <time.h>
#include "../json/include/json-c/json.h"
#include "../data_base/inc/dbase.h"

typedef struct s_u_login_info {
    int u_id;
    char u_login[256];
    char u_passwd[256];
    char u_message[256];
} t_u_login_info;

#endif
