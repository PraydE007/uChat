#ifndef CLIENT_H
#define CLIENT_H

#include "../../inc/general.h"
#include <strings.h>
#include <gtk/gtk.h>
#include "../../libmx/inc/libmx.h"
#include "../../json/include/json-c/json.h"
#include <openssl/ssl.h>

#define MX_WINDOW_LOGIN "client/res/forms/window.login.glade"
#define MX_WINDOW_SIGNUP "client/res/forms/window.signup.glade"
#define MX_WINDOW_CHAT "client/res/forms/window.chat.glade"

#define MX_DEF_THEME "client/res/themes/light.css"
#define MX_DARK_THEME "client/res/themes/dark.css"

typedef struct s_s_glade {
    bool darkmode;
    int sockfd;

    // Login window
    GtkWidget *w_signin;
    GtkWidget *f_panel;
    GtkWidget *e_l_login;
    GtkWidget *e_l_password;
    GtkWidget *b_l_signin;
    GtkWidget *b_l_signup;
    GtkWidget *b_settings;

    // Settings window
    GtkWidget *w_settings;
    GtkWidget *b_close;
    GtkWidget *s_darkmode;

    // Registration window
    GtkWidget *w_signup;
    GtkWidget *b_r_signup;
    GtkWidget *e_email;
    GtkWidget *e_r_login;
    GtkWidget *e_r_password;
    GtkWidget *e_r_password2;
    GtkWidget *b_r_signin;

    // Chat window
    GtkWidget *w_chat;
    GtkWidget *b_send;
    GtkWidget *e_message;
    GtkWidget *tv_term_emul;
}              t_s_glade;

// HASH
char *mx_hash_to_string(unsigned char *hash);
char *mx_hash(char *pass);

// GUI
void mx_interface(int *argc, char ***argv, int socket);
t_s_glade *mx_init_auth_screen(int socket);
GtkWidget *mx_get_widget(GtkBuilder **b, char *id);
void mx_load_theme(t_s_glade *gui);
void mx_logged_in_chat(t_s_glade *gui);

// GUI SIGNALS
void mx_open_auth_settings(GtkButton *button, gpointer data);
void mx_close_auth_settings(GtkButton *button, gpointer data);
void mx_darkmode_switch(GtkSwitch *s_switch, gpointer data);
void mx_logged_in(GtkButton *button, gpointer data);
void mx_open_signup(GtkButton *button, gpointer data);
void mx_close_signup(GtkButton *button, gpointer data);
void mx_registration(GtkButton *button, gpointer data);

#endif
