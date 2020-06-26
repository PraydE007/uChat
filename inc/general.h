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
#include "../libmx/inc/libmx.h"
#include <pthread.h>

#define MX_LOG "1"
#define MX_LOG_MES "You have logged in!"
#define MX_REG "2"
#define MX_REG_MES "You have registered successfully!"
#define MX_ERRLOG "3"
#define MX_ERR_LOG "Login or password is incorrect!"
#define MX_ERRREG "4"
#define MX_ERR_REG "User already exist!"

typedef struct s_u_login_info {
    int u_id;
    char u_login[256];
    char u_passwd[256];
    char u_message[256];
} t_u_login_info;

#endif
