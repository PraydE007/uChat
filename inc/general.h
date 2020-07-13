#ifndef GENERAL_H
#define GENERAL_H

#define MX_MAX_BYTES 2048

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

#define MX_CHEAT_MESSAGE "Just stay on your place and wait for police!"
#define MX_SECURITY_KEY "cdef9e974ae775ea9b1472cedb108607127607e538b5c1ff8f9e4"
#define MX_LOG "1"
#define MX_LOG_MES "You have logged in!"
#define MX_REG "2"
#define MX_REG_MES "You have registered successfully!"
#define MX_ERRLOG "3"
#define MX_LOG_ERR "Login or password is incorrect!"
#define MX_ERRREG "4"
#define MX_REG_CHAT_ERR "A chat or an user with such name already exists!!"
#define MX_CONT "5"
#define MX_CONT_MES "The contact was added!"
#define MX_ERRCONT "6"
#define MX_CONT_ERR "There is no such user in the uchat!"
#define MX_CHAT "7"
#define MX_CHAT_MES "The chat was created!"
#define MX_PRIVATE_CHAT "You can add contact to private chat!"
#define MX_CONT_ADD_CHAT "The user was added to the chat!"
#define MX_DEL_CHAT_MES "The contact was deleted from the chat!"
#define MX_ERR_DEL_CHAT "You can not delete users from this chat!"

typedef struct s_u_login_info {
    int u_id;
    char u_login[256];
    char u_passwd[256];
    char u_message[256];
} t_u_login_info;

#endif
