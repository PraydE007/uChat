#ifndef CLIENT_H
#define CLIENT_H

#include "../../inc/general.h"
#include <gtk/gtk.h>
#include "../../json/include/json-c/json.h"
#include <openssl/ssl.h>

typedef struct s_interface {
    GtkWidget *window;
    GtkWidget *box;
    GtkWidget *button_login;
    GtkWidget *button_register;
    GtkWidget *entry_login;
    GtkWidget *entry_passwd;
} t_interface;

void mx_init_auth_screen();
void mx_interface(int argc, char *argv[]);
char *mx_hash_to_string(unsigned char *hash);
char *mx_hash(char *login, char *pass);
#endif
