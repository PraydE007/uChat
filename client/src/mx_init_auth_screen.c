#include "client.h"

static void connect_signals(t_s_glade *gui) {
    mx_init_signal_1(gui);
    mx_init_signal_2(gui);
    mx_init_signal_3(gui);
    mx_init_signal_4(gui);
    mx_init_signal_5(gui);
    mx_init_signal_6(gui);
    mx_init_signal_7(gui);
    mx_init_signal_8(gui);
    mx_init_signal_9(gui);
    mx_init_signal_10(gui);
    mx_init_signal_11(gui);
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
    mx_init_login(&builder, &gui);
    mx_init_signup(&builder, &gui);
    mx_init_chat(&builder, &gui);
    mx_init_edit(&builder, &gui);
    mx_init_profile(&builder, &gui);
    mx_init_group(&builder, &gui);
    mx_init_images(&gui);
    mx_load_theme(gui);
    connect_signals(gui);
    gtk_widget_show_all(gui->w_signin);
    pthread_create(&x, NULL, mx_client_recv, (void *)&gui);
    gtk_main();
    return gui;
}
