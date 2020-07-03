#ifndef CLIENT_H
#define CLIENT_H

#include "../../inc/general.h"
#include <ctype.h>
#include <strings.h>
#include <gtk/gtk.h>
#include "../../libmx/inc/libmx.h"
#include "../../json/include/json-c/json.h"
#include <openssl/ssl.h>

// #define MX_AVATAR_MIS "client/res/images/avatar_missing.png"
#define MX_AVATAR_MIS "client/res/images/meme.png"
#define MX_BUTTON_PROFILE "client/res/icons/profile.png"
#define MX_BUTTON_LOGOUT "client/res/icons/logout.png"
#define MX_BUTTON_FIND "client/res/icons/search.png"
#define MX_BUTTON_SETTINGS "client/res/icons/settings.png"
#define MX_BUTTON_EMOJI "client/res/icons/smile.png"
#define MX_BUTTON_SEND "client/res/icons/send.png"

#define MX_WINDOW_WARNING "client/res/icons/warning.png"
#define MX_WINDOW_LOGIN "client/res/forms/window.login.glade"
#define MX_WINDOW_SIGNUP "client/res/forms/window.signup.glade"
#define MX_WINDOW_CHAT "client/res/forms/window.chat.glade"
#define MX_WINDOW_PROFILE "client/res/forms/window.profile.glade"

#define MX_DEF_THEME "client/res/themes/light.css"
#define MX_DARK_THEME "client/res/themes/dark.css"

typedef struct s_s_glade {
    int mode;
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
    GtkWidget *b_l_settings;

    // Settings window
    GtkWidget *w_settings;
    GtkWidget *b_t_light;
    GtkWidget *b_t_dark;
    GtkWidget *b_t_custom;
    GtkWidget *b_t_connect;
    GtkWidget *b_s_close;
    GtkWidget *e_package;

    // Registration window
    GtkWidget *w_signup;
    GtkWidget *b_r_signup;
    GtkWidget *e_email;
    GtkWidget *e_r_login;
    GtkWidget *e_r_password;
    GtkWidget *e_r_password2;
    GtkWidget *b_r_signin;
    GtkWidget *e_r_mobile;

    // Chat window
    GtkWidget *w_chat;
    GtkWidget *b_send;
    GtkWidget *i_b_send;
    GtkWidget *b_profile;
    GtkWidget *i_b_profile;
    GtkWidget *b_logout;
    GtkWidget *i_b_logout;
    GtkWidget *b_c_settings;
    GtkWidget *i_b_settings;
    GtkWidget *b_emoji;
    GtkWidget *i_b_emoji;
    GtkWidget *e_message;
    GtkWidget *e_find;
    GtkWidget *b_find;
    GtkWidget *i_b_find;
    GtkWidget *l_chats;
    GtkWidget *l_messages;

    // Emoji window
    GtkWidget *w_emoji;
    GtkWidget *b_e_close;
    GtkWidget *l_one;

    // Profile window
    GtkWidget *w_profile;
    GtkWidget *i_avatar;
    GtkWidget *e_p_login;
    GtkWidget *e_p_email;
    GtkWidget *e_p_number;
    GtkWidget *b_password;
    GtkWidget *b_p_apply;
    GtkWidget *b_p_close;

    // Password window
    GtkWidget *w_password;
    GtkWidget *e_p_oldpass;
    GtkWidget *e_p_newpass1;
    GtkWidget *e_p_newpass2;
    GtkWidget *b_pp_apply;
    GtkWidget *b_pp_close;
}              t_s_glade;

// BUFFERS_PROFILE_STRUCTS_FOR_AUDITOR
typedef struct s_buff_getchar_prof {
    char *login;
    char *email;
    char *number;
}   t_buff_getchar_prof;

typedef struct s_change_prof {
    char *login;
    char *email;
    char *mobile;
    char *new_login;
}   t_change_prof;

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
void mx_rep_img(GtkWidget *image, const char *filename, int w, int h);
void mx_show_dialog(GtkWidget *parent, char *message);

// GUI SIGNALS
void mx_open_window(GtkButton *button, gpointer data);
void mx_close_window(GtkButton *button, gpointer data);
void mx_light_theme(GtkButton *b, gpointer data);
void mx_dark_theme(GtkButton *b, gpointer data);
void mx_logged_in(GtkButton *button, gpointer data);
void mx_open_signup(GtkButton *button, gpointer data);
void mx_close_signup(GtkButton *button, gpointer data);
void mx_registration(GtkButton *button, gpointer data);
void mx_send_message(GtkButton *button, gpointer data);
void mx_open_profile(GtkButton *button, gpointer data);
void mx_close_profile(GtkButton *button, gpointer data);
void mx_push_message(GtkWidget *lst, const char *msg);
void mx_change_theme(t_s_glade *gui, bool mode);
void mx_change_profile(GtkButton *button, gpointer data);
void mx_anti_resize(GtkWindow *w, GdkEventWindowState *e, gpointer data);

//infinity_recive_from_server
void *mx_client_recv(void *data);

#endif
