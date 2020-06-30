#include "client.h"

void mx_change_theme(t_s_glade *gui, bool mode) {
    char *theme = MX_DEF_THEME;

    if (mode)
        theme = MX_DARK_THEME;
    gtk_css_provider_load_from_path(gui->css_provider, theme, NULL);
}
