#include "client.h"

void mx_load_theme(t_s_glade *gui) {
    GtkCssProvider *css_provider = gtk_css_provider_new();
    char *theme = MX_DEF_THEME;

    if (gui->darkmode)
        theme = MX_DARK_THEME;
    gtk_css_provider_load_from_path(css_provider, theme, NULL);
    gtk_style_context_add_provider_for_screen(
        gdk_screen_get_default(),
        GTK_STYLE_PROVIDER(css_provider),
        GTK_STYLE_PROVIDER_PRIORITY_USER
    );
}
