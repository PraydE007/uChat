#include "client.h"

void mx_load_theme(t_s_glade *gui) {
    gui->css_provider = gtk_css_provider_new();
    char *theme = MX_DEF_THEME;

    if (gui->mode == 1)
        theme = MX_DARK_THEME;
        gtk_css_provider_load_from_path(gui->css_provider, theme, NULL);
        gtk_style_context_add_provider_for_screen(
        gdk_screen_get_default(),
        GTK_STYLE_PROVIDER(gui->css_provider),
        GTK_STYLE_PROVIDER_PRIORITY_USER
    );
}
