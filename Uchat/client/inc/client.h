#ifndef CLIENT_H
#define CLIENT_H

#include "../inc/general.h"
#include <gtk/gtk.h>

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

#endif
