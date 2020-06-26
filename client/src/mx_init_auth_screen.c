#include "client.h"

static void init_login(GtkBuilder **builder, t_s_glade **gui) {
    (*builder) = gtk_builder_new_from_file(MX_WINDOW_LOGIN);
    (*gui)->w_signin = mx_get_widget(builder, "window.login");
    (*gui)->e_l_login = mx_get_widget(builder, "entry.login");
    (*gui)->e_l_password = mx_get_widget(builder, "entry.password");
    (*gui)->b_l_signin = mx_get_widget(builder, "button.signin");
    (*gui)->b_l_signup = mx_get_widget(builder, "button.signup");
    (*gui)->b_settings = mx_get_widget(builder, "button.settings");
    (*gui)->w_settings = mx_get_widget(builder, "window.settings");
    (*gui)->b_s_close = mx_get_widget(builder, "button.close");
    (*gui)->s_darkmode = mx_get_widget(builder, "switch.darkmode");

    if ((*gui)->darkmode)
        gtk_switch_set_active(GTK_SWITCH((*gui)->s_darkmode), true);

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
}

static void init_chat(GtkBuilder **builder, t_s_glade **gui) {
    (*builder) = gtk_builder_new_from_file(MX_WINDOW_CHAT);
    (*gui)->w_chat = mx_get_widget(builder, "window.chat");
    (*gui)->b_send = mx_get_widget(builder, "button.send");
    (*gui)->b_profile = mx_get_widget(builder, "button.profile");
    (*gui)->e_message = mx_get_widget(builder, "entry.message");
    (*gui)->tv_term_emul = mx_get_widget(builder, "tv.term_emul");
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

static void connect_signals(t_s_glade *gui) {
    // UChat Quit Signals
    g_signal_connect(gui->w_signin, "destroy",
                    G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(gui->w_signup, "destroy",
                    G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(gui->w_chat, "destroy",
                    G_CALLBACK(gtk_main_quit), NULL);

    // Login Window Signals
    g_signal_connect(gui->b_l_signin, "clicked",
                    G_CALLBACK(mx_logged_in), gui);
    g_signal_connect(gui->b_l_signup, "clicked",
                    G_CALLBACK(mx_open_signup), gui);
    g_signal_connect(gui->b_settings, "clicked",
                    G_CALLBACK(mx_open_auth_settings), gui->w_settings);

    // Settings Window Signals
    g_signal_connect(gui->b_s_close, "clicked",
                    G_CALLBACK(mx_close_auth_settings), gui->w_settings);
    g_signal_connect(gui->s_darkmode, "state-set",
                    G_CALLBACK(mx_darkmode_switch), gui);

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

    // Profile Window Signals
    g_signal_connect(gui->b_p_close, "clicked",
                    G_CALLBACK(mx_close_profile), gui);
}

static bool read_mode(void) {
    int file = open("settings.json", O_RDONLY);
    char *json = mx_strnew(1024);
    struct json_object *settings = NULL;
    struct json_object *darkmode = NULL;
    bool res = false;

    if (file != -1) {
        read(file, json, 1024);
        close(file);
        settings = json_tokener_parse(json);
        darkmode = json_object_object_get(settings, "darkmode");
        mx_strdel(&json);
        res = json_object_get_boolean(darkmode);
        json_object_put(settings);
        return res;
    }
    mx_strdel(&json);
    return false;
}

t_s_glade *mx_init_auth_screen(int socket) {
    GtkBuilder *builder = NULL;
    t_s_glade *gui = (t_s_glade *)malloc(sizeof(t_s_glade));

    gui->darkmode = read_mode();
    gui->sockfd = socket;
    init_login(&builder, &gui);
    init_signup(&builder, &gui);
    init_chat(&builder, &gui);
    init_profile(&builder, &gui);
    mx_load_theme(gui);
    connect_signals(gui);
    gtk_widget_show_all(gui->w_signin);
    gtk_main();
    return gui;
}
