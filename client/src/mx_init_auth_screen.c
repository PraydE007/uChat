#include "client.h"

static void init_login(GtkBuilder **builder, t_s_glade **gui) {
    (*builder) = gtk_builder_new_from_file(MX_WINDOW_LOGIN);
    (*gui)->w_signin = mx_get_widget(builder, "window.login");
    (*gui)->e_l_login = mx_get_widget(builder, "entry.login");
    (*gui)->e_l_password = mx_get_widget(builder, "entry.password");
    (*gui)->b_l_signin = mx_get_widget(builder, "button.signin");
    (*gui)->b_l_signup = mx_get_widget(builder, "button.signup");
    (*gui)->b_l_settings = mx_get_widget(builder, "button.settings");
    (*gui)->w_settings = mx_get_widget(builder, "window.settings");
    (*gui)->b_s_close = mx_get_widget(builder, "button.close");
    (*gui)->b_t_light = mx_get_widget(builder, "button.theme.light");
    (*gui)->b_t_dark = mx_get_widget(builder, "button.theme.dark");
    (*gui)->b_t_custom = mx_get_widget(builder, "button.theme.custom");
    (*gui)->b_t_connect = mx_get_widget(builder, "button.theme.connect");

    // (*gui)->icon = gdk_pixbuf_new_from_file("client/res/images/icon.ico", NULL);
    // if ((*gui)->icon) {
    //     printf("ICON OK!\n");
    //     gtk_window_set_icon(GTK_WINDOW((*gui)->w_signin), (*gui)->icon);
    // }
}

static void init_signup(GtkBuilder **builder, t_s_glade **gui) {
    (*builder) = gtk_builder_new_from_file(MX_WINDOW_SIGNUP);
    (*gui)->w_signup = mx_get_widget(builder, "window.signup");
    (*gui)->b_r_signup = mx_get_widget(builder, "button.signup");
    (*gui)->e_email = mx_get_widget(builder, "entry.email");
    (*gui)->e_r_login = mx_get_widget(builder, "entry.login");
    (*gui)->e_r_password = mx_get_widget(builder, "entry.password");
    (*gui)->e_r_password2 = mx_get_widget(builder, "entry.password2");
    (*gui)->b_r_signin = mx_get_widget(builder, "button.login");
    (*gui)->e_r_mobile = mx_get_widget(builder, "entry.phone");
}

static void init_chat(GtkBuilder **builder, t_s_glade **gui) {
    (*builder) = gtk_builder_new_from_file(MX_WINDOW_CHAT);
    (*gui)->w_chat = mx_get_widget(builder, "window.chat");
    (*gui)->b_send = mx_get_widget(builder, "button.send");
    (*gui)->i_b_send = mx_get_widget(builder, "image.button.send");
    (*gui)->b_profile = mx_get_widget(builder, "button.profile");
    (*gui)->i_b_profile = mx_get_widget(builder, "image.button.profile");
    (*gui)->b_logout = mx_get_widget(builder, "button.profile");
    (*gui)->i_b_logout = mx_get_widget(builder, "image.button.logout");
    (*gui)->b_c_settings = mx_get_widget(builder, "button.settings");
    (*gui)->i_b_settings = mx_get_widget(builder, "image.button.settings");
    (*gui)->e_message = mx_get_widget(builder, "entry.message");
    (*gui)->e_find = mx_get_widget(builder, "entry.find");
    (*gui)->b_find = mx_get_widget(builder, "button.find");
    (*gui)->i_b_find = mx_get_widget(builder, "image.button.find");
    (*gui)->l_chats = mx_get_widget(builder, "list.chats");
    (*gui)->l_messages = mx_get_widget(builder, "list.messages");
    (*gui)->w_emoji = mx_get_widget(builder, "window.emoji");
    (*gui)->b_emoji = mx_get_widget(builder, "button.emoji");
    (*gui)->i_b_emoji = mx_get_widget(builder, "image.button.emoji");
    (*gui)->b_e_close = mx_get_widget(builder, "button.close");
    (*gui)->l_one = mx_get_widget(builder, "label.one");
    // gtk_label_set_text(GTK_LABEL((*gui)->l_one), "\U0001F600 <-");
}

static void init_profile(GtkBuilder **builder, t_s_glade **gui) {
    (*builder) = gtk_builder_new_from_file(MX_WINDOW_PROFILE);
    (*gui)->w_profile = mx_get_widget(builder, "window.profile");
    (*gui)->i_avatar = mx_get_widget(builder, "image.avatar");
    (*gui)->e_p_login = mx_get_widget(builder, "entry.login");
    (*gui)->e_p_email = mx_get_widget(builder, "entry.email");
    (*gui)->e_p_number = mx_get_widget(builder, "entry.number");
    (*gui)->e_p_oldpass = mx_get_widget(builder, "entry.oldpass");
    (*gui)->e_p_newpass1 = mx_get_widget(builder, "entry.newpass1");
    (*gui)->e_p_newpass2 = mx_get_widget(builder, "entry.newpass2");
    (*gui)->b_p_apply = mx_get_widget(builder, "button.apply");
    (*gui)->b_p_close = mx_get_widget(builder, "button.close");
}

static void init_images(t_s_glade **gui) {
    mx_rep_img((*gui)->i_avatar, MX_AVATAR_MIS, 225, 225);
    mx_rep_img((*gui)->i_b_profile, MX_BUTTON_PROFILE, 32, 32);
    mx_rep_img((*gui)->i_b_logout, MX_BUTTON_LOGOUT, 32, 32);
    mx_rep_img((*gui)->i_b_find, MX_BUTTON_FIND, 25, 25);
    mx_rep_img((*gui)->i_b_settings, MX_BUTTON_SETTINGS, 25, 25);
    mx_rep_img((*gui)->i_b_emoji, MX_BUTTON_EMOJI, 25, 25);
    mx_rep_img((*gui)->i_b_send, MX_BUTTON_SEND, 25, 25);
}

static void connect_signals(t_s_glade *gui) {
    // Uchat Quit Signals
    g_signal_connect(gui->w_signin, "destroy",
                    G_CALLBACK(exit), (void *)0);
    g_signal_connect(gui->w_signup, "destroy",
                    G_CALLBACK(exit), (void *)0);
    g_signal_connect(gui->w_chat, "destroy",
                    G_CALLBACK(exit), (void *)0);
    g_signal_connect(gui->w_profile, "destroy",
                    G_CALLBACK(exit), (void *)0);

    // Login Window Signals
    g_signal_connect(gui->b_l_signin, "clicked",
                    G_CALLBACK(mx_logged_in), gui);
    g_signal_connect(gui->b_l_signup, "clicked",
                    G_CALLBACK(mx_open_signup), gui);
    g_signal_connect(gui->b_l_settings, "clicked",
                    G_CALLBACK(mx_open_window), gui->w_settings);

    // Settings Window Signals
    g_signal_connect(gui->b_s_close, "clicked",
                    G_CALLBACK(mx_close_window), gui->w_settings);
    g_signal_connect(gui->b_t_light, "clicked",
                    G_CALLBACK(mx_light_theme), gui);
    g_signal_connect(gui->b_t_dark, "clicked",
                    G_CALLBACK(mx_dark_theme), gui);

    // Registration Window Signals
    g_signal_connect(gui->b_r_signin, "clicked",
                    G_CALLBACK(mx_close_signup), gui);
    g_signal_connect(gui->b_r_signup, "clicked",
                    G_CALLBACK(mx_registration), gui);

    // Chat Window Signals
    g_signal_connect(gui->b_send, "clicked",
                    G_CALLBACK(mx_send_message), gui);
    g_signal_connect(gui->b_profile, "clicked",
                    G_CALLBACK(mx_open_profile), gui);
    g_signal_connect(gui->b_find, "clicked",
                    G_CALLBACK(mx_find_user), gui);
    g_signal_connect(gui->b_c_settings, "clicked",
                    G_CALLBACK(mx_open_window), gui->w_settings);
    g_signal_connect(gui->b_emoji, "clicked",
                    G_CALLBACK(mx_open_window), gui->w_emoji);

    // Emoji window
    g_signal_connect(gui->b_e_close, "clicked",
                    G_CALLBACK(mx_close_window), gui->w_emoji);

    // Profile Window Signals
    g_signal_connect(gui->b_p_close, "clicked",
                    G_CALLBACK(mx_close_profile), gui);
    g_signal_connect(gui->b_p_apply, "clicked",
                    G_CALLBACK(mx_change_profile), gui);
}

static bool read_mode(void) {
    int file = open("settings.json", O_RDONLY);
    char *json = mx_strnew(1024);
    struct json_object *settings = NULL;
    struct json_object *thememode = NULL;
    int res = 0;

    if (file != -1) {
        read(file, json, 1024);
        close(file);
        settings = json_tokener_parse(json);
        thememode = json_object_object_get(settings, "mode");
        mx_strdel(&json);
        res = json_object_get_boolean(thememode);
        json_object_put(settings);
        return res;
    }
    mx_strdel(&json);
    return false;
}

t_s_glade *mx_init_auth_screen(int socket) {
    GtkBuilder *builder = NULL;
    t_s_glade *gui = (t_s_glade *)malloc(sizeof(t_s_glade));
    pthread_t x;

    gui->mode = read_mode();
    gui->sockfd = socket;
    init_login(&builder, &gui);
    init_signup(&builder, &gui);
    init_chat(&builder, &gui);
    init_profile(&builder, &gui);
    init_images(&gui);
    mx_load_theme(gui);
    connect_signals(gui);
    gtk_widget_show_all(gui->w_signin);
    pthread_create(&x, NULL, mx_client_recv, (void *)&gui);
    gtk_main();
    return gui;
}
