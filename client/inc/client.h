#ifndef CLIENT_H
#define CLIENT_H

#include "../../inc/general.h"
#include <ctype.h>
#include <strings.h>
#include <gtk/gtk.h>
#include <sys/stat.h>
#include "../../libmx/inc/libmx.h"
#include "../../json/include/json-c/json.h"
#include <openssl/ssl.h>

#define MX_G_A_MIS "client/res/images/group_avatar_missing.png"
#define MX_AVATAR_MIS "client/res/images/avatar_missing.png"
#define MX_MEME_AVATAR "client/res/images/meme_avatar.png"
#define MX_BUTTON_PROFILE "client/res/icons/profile.png"
#define MX_BUTTON_LOGOUT "client/res/icons/logout.png"
#define MX_BUTTON_FIND "client/res/icons/search.png"
#define MX_BUTTON_SETTINGS "client/res/icons/settings.png"
#define MX_BUTTON_EMOJI "client/res/icons/smile.png"
#define MX_BUTTON_SEND "client/res/icons/send.png"
#define MX_BUTTON_BAN "client/res/icons/ban.png"
#define MX_BUTTON_GROUP "client/res/icons/group.png"
#define MX_BUTTON_RESET "client/res/icons/reset.png"
#define MX_BUTTON_FILE "client/res/icons/file.png"
#define MX_BUTTON_EDIT "client/res/icons/edit.png"
#define MX_BUTTON_APPLY "client/res/icons/mark.png"

#define MX_WINDOW_WARNING "client/res/icons/warning.png"
#define MX_WINDOW_LOGIN "client/res/forms/window.login.glade"
#define MX_WINDOW_SIGNUP "client/res/forms/window.signup.glade"
#define MX_WINDOW_CHAT "client/res/forms/window.chat.glade"
#define MX_WINDOW_PROFILE "client/res/forms/window.profile.glade"
#define MX_WINDOW_GROUP "client/res/forms/window.group.glade"
#define MX_WINDOW_EDIT "client/res/forms/window.edit.glade"

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
    GtkWidget *b_group;
    GtkWidget *i_b_group;
    GtkWidget *l_chats;
    GtkWidget *l_messages;
    GtkWidget *s_w_messages;
    GtkWidget *b_u_file;
    GtkWidget *i_b_u_file;
    GtkWidget *b_c_pad;
    GtkWidget *b_u_profile;
    GtkWidget *i_b_u_profile;
    GtkWidget *b_r_chat;
    GtkWidget *i_b_r_chat;
    GtkWidget *s_filter;
    GtkWidget *b_edit;
    GtkWidget *i_b_edit;

    // Edit window
    gint tag;
    GtkWidget *w_edit;
    GtkWidget *l_l_count;
    GtkWidget *tv_editor;
    GtkWidget *b_e_apply;
    GtkWidget *i_b_e_apply;

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

    // Group window
    GtkWidget *w_group;
    GtkWidget *i_group;
    GtkWidget *e_image;
    GtkWidget *e_group_name;
    GtkWidget *e_g_nickname;
    GtkWidget *b_g_close;
    GtkWidget *b_f_image;
    GtkWidget *i_f_image;
    GtkWidget *b_i_reset;
    GtkWidget *i_i_reset;
    GtkWidget *b_f_user;
    GtkWidget *i_b_f_user;
    GtkWidget *b_b_user;
    GtkWidget *i_b_user;
    GtkWidget *b_g_apply;
    GtkWidget *l_g_group;

    //key
    char *key;
    GtkWidget *b_pp_apply;
    GtkWidget *b_pp_close;

    //recv_data
    char buffer[MX_MAX_BYTES];
    char *recv_data;

    //sending
    char *send_to;
    char **contacts;
    char **chats;
    int if_contact;
    pthread_mutex_t mutex;

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
    char *key;
}   t_change_prof;

typedef struct s_verbs {
    char *bad_verbs;
    char *bad_words;
    char *good_verbs;
    char *good_words;
}   t_verbs;

typedef struct s_splited_verbs {
    char **bad_verbs;
    char **bad_words;
    char **good_verbs;
    char **good_words;
}   t_splitetd_verbs;
// VALIDATION
int mx_check_number(const char *number, int j);
int mx_check_pass(const char *pass, int j);
int mx_check_login(const char *login, int j);
int mx_check_mail(const char *mail, int i);

// HASH
char *mx_hash_to_string(unsigned char *hash);
char *mx_hash(char *pass);

//cat_message
char *mx_cat_message(char *message);

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
void mx_p_own(GtkWidget *lst, const char *msg, const char *name);
void mx_p_owned(GtkWidget *lst, const char *msg, const char *name);
void mx_clear_container(GtkWidget *con);
char *mx_open_file_chooser(GtkWindow *parent);
gint mx_editor_update_lst(gpointer data);

// GUI SIGNALS
void mx_send_image(const char *file, int sockfd);
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
void mx_change_pass(GtkButton *button, gpointer data);
void mx_push_message(GtkWidget *lst, const char *msg, const char *owner);
void mx_change_theme(t_s_glade *gui, bool mode);
void mx_change_profile(GtkButton *button, gpointer data);
void mx_anti_resize(GtkWindow *w, GdkEventWindowState *e, gpointer data);
void mx_open_chat(GtkListBox *box, GtkListBoxRow *row, gpointer data);
void mx_open_group(GtkButton *btn, gpointer data);
void mx_close_group(GtkButton *btn, gpointer data);
void mx_upload_file(GtkButton *btn, gpointer data);
void mx_add_user_to_group(GtkButton *btn, gpointer data);
void mx_delete_contact(GtkButton *btn, gpointer data);
void mx_apply_group(GtkButton *btn, gpointer data);
void mx_delete_user_from_chat(GtkButton *btn, gpointer data);
void mx_view_profile(GtkButton *btn, gpointer data);
char *mx_init_filter(char *message);
//infinity_recive_from_server
void *mx_client_recv(void *data);
void mx_open_editor(GtkButton *button, gpointer data);
void mx_editor_apply(GtkButton *button, gpointer data);

//successes
gboolean mx_error_create_chat(void *data);
gboolean mx_error_find_user(void *data);
gboolean mx_error_logging(void *data);
gboolean mx_success_logging(void *data);
gboolean mx_success_registr(void *data);
gboolean mx_success_profile(void *data);
gboolean mx_success_change_profile(void *data);
gboolean mx_success_change_passwd(void *data);
gboolean mx_success_add_contact(void *data);
gboolean mx_success_message(void *data);
gboolean mx_success_history(void *data);
gboolean mx_success_invited(void *data);
gboolean mx_success_update_contacts(void *data);
gboolean mx_success_public_message(void *data);
gboolean mx_success_members_list(void *data);

//If_login_render
gboolean mx_render_contacts(t_s_glade *gui);
gboolean mx_render_chats(t_s_glade *gui);

#endif
