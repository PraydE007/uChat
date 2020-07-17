#include "client.h"

void mx_rep_img_auto(GtkWidget *image, const char *filename, int w, int h) {
    GdkPixbuf *pxbs;
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(filename, NULL);
    gint pw = gdk_pixbuf_get_width(pixbuf);
    gint ph = gdk_pixbuf_get_height(pixbuf);

    if (pixbuf) {
        if (pw > w || ph > h)
            pxbs = gdk_pixbuf_scale_simple(pixbuf, w, h, GDK_INTERP_BILINEAR);
        else
            pxbs = gdk_pixbuf_scale_simple(pixbuf, pw, ph, GDK_INTERP_BILINEAR);
        gtk_image_set_from_pixbuf(GTK_IMAGE(image), pxbs);
        g_object_unref(pxbs);
        g_object_unref(pixbuf);
    }
}
