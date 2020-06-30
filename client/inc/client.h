#ifndef _GNU_SOURCE
#define _GNU_SOURCE 1
#endif

#ifndef CLIENT_H
#define CLIENT_H

#include "../../inc/general.h"
#include <ctype.h>
#include <strings.h>
#include <gtk/gtk.h>
#include "../../libmx/inc/libmx.h"
#include "../../json/include/json-c/json.h"
#include <openssl/ssl.h>

#define MX_AVATAR_MIS "client/res/images/avatar_missing.png"

#define MX_WINDOW_LOGIN "client/res/forms/window.login.glade"
#define MX_WINDOW_SIGNUP "client/res/forms/window.signup.glade"
#define MX_WINDOW_CHAT "client/res/forms/window.chat.glade"
#define MX_WINDOW_PROFILE "client/res/forms/window.profile.glade"

#define MX_DEF_THEME "client/res/themes/light.css"
#define MX_DARK_THEME "client/res/themes/dark.css"

typedef struct s_s_glade {
    bool darkmode;
    int sockfd;

    // Window position
    gint w_x;
    gint w_y;

    // Application
    GdkPixbuf *icon;
    GtkCssProvider *css_provider;

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
    GtkWidget *b_s_close;
    GtkWidget *s_darkmode;

    // Registration window
    GtkWidget *w_signup;
    GtkWidget *b_r_signup;
    GtkWidget *e_email;
    GtkWidget *e_r_login;
    GtkWidget *e_r_password;
    GtkWidget *e_r_password2;
    GtkWidget *b_r_signin;
    GtkWidget *e_r_number;

    // Chat window
    GtkWidget *w_chat;
    GtkWidget *b_send;
    GtkWidget *b_profile;
    GtkWidget *e_message;
    GtkWidget *e_find;
    GtkWidget *b_find;
    GtkWidget *l_chats;
    GtkWidget *l_messages;

    // Profile window
    GtkWidget *w_profile;
    GtkWidget *i_avatar;
    GtkWidget *e_p_login;
    GtkWidget *e_p_email;
    GtkWidget *e_p_number;
    GtkWidget *e_p_oldpass;
    GtkWidget *e_p_newpass1;
    GtkWidget *e_p_newpass2;
    GtkWidget *b_p_apply;
    GtkWidget *b_p_close;
}              t_s_glade;

// VALIDATION
int mx_check_number(const char *number, int j);
int mx_check_pass(const char *pass, int j);
int mx_check_login(const char *login, int j);
int mx_check_mail(const char *mail, int i);

// HASH
char *mx_hash_to_string(unsigned char *hash);
char *mx_hash(char *pass);

// GUI
void mx_interface(int *argc, char ***argv, int socket);
t_s_glade *mx_init_auth_screen(int socket);
GtkWidget *mx_get_widget(GtkBuilder **b, char *id);
void mx_load_theme(t_s_glade *gui);
void mx_logged_in_chat(t_s_glade *gui);
GtkWindow *mx_gw(GtkWidget *widget);
GtkWidget *mx_load_img(const char *filename, int w, int h);
void mx_push_chat(GtkWidget *lst, const char *user_name);
void mx_find_user(GtkButton *button, gpointer data);

// GUI SIGNALS
void mx_open_auth_settings(GtkButton *button, gpointer data);
void mx_close_auth_settings(GtkButton *button, gpointer data);
void mx_darkmode_switch(GtkSwitch *s_switch, gpointer data);
void mx_logged_in(GtkButton *button, gpointer data);
void mx_open_signup(GtkButton *button, gpointer data);
void mx_close_signup(GtkButton *button, gpointer data);
void mx_registration(GtkButton *button, gpointer data);
void mx_send_message(GtkButton *button, gpointer data);
void mx_open_profile(GtkButton *button, gpointer data);
void mx_close_profile(GtkButton *button, gpointer data);
void mx_push_message(GtkWidget *lst, const char *msg);
void mx_change_theme(t_s_glade *gui, bool mode);

//infinity_recive_from_server
void *mx_client_recv(void *data);

#endif
