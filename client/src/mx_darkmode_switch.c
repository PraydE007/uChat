#include "client.h"

static void rewrite(struct json_object *obj) {
    int file = open("settings.json", O_RDWR | O_TRUNC);
    const char *json = json_object_to_json_string(obj);

    write(file, json, mx_strlen(json));
    close(file);
}

static void write_mode(bool res) {
    int file = open("settings.json", O_RDWR);
    char *json = mx_strnew(1024);
    struct json_object *settings = NULL;
    struct json_object *darkmode = NULL;

    if (file != -1) {
        read(file, json, 1024);
        close(file);
        settings = json_tokener_parse(json);
        darkmode = json_object_object_get(settings, "darkmode");
        if (json_object_set_boolean(darkmode, res))
            rewrite(settings);
        json_object_put(settings);
    }
    mx_strdel(&json);
}

void mx_darkmode_switch(GtkSwitch *s_switch, gpointer data) {
    t_s_glade *gui = (t_s_glade *)data;

    mx_printstr("1\n");
    (void)s_switch;
    mx_printstr("2\n");
    write_mode(!(gui->darkmode));
    mx_printstr("3\n");
}
