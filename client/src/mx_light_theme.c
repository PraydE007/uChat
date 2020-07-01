#include "client.h"

static void rewrite(struct json_object *obj) {
    int file = open("settings.json", O_RDWR | O_TRUNC);
    const char *json = json_object_to_json_string_ext(obj,
                                                      JSON_C_TO_STRING_PRETTY);

    write(file, json, mx_strlen(json));
    close(file);
}

static void write_mode(int res) {
    int file = open("settings.json", O_RDWR);
    char *json = mx_strnew(1024);
    struct json_object *settings = NULL;
    struct json_object *thememode = NULL;

    if (file != -1) {
        read(file, json, 1024);
        close(file);
        settings = json_tokener_parse(json);
        thememode = json_object_object_get(settings, "mode");
        if (json_object_set_int(thememode, res))
            rewrite(settings);
        json_object_put(settings);
    }
    mx_strdel(&json);
}

void mx_light_theme(GtkButton *b, gpointer data) {
    t_s_glade *gui = (t_s_glade *)data;

    (void)b;
    gtk_css_provider_load_from_path(gui->css_provider, MX_DEF_THEME, NULL);
    write_mode(0);
}
