#include "client.h"

GtkWidget *mx_load_img(const char *filename, int w, int h) {
   GdkPixbuf *pxbscaled;
   GtkWidget *image = gtk_image_new();
   GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(filename, NULL);

   pxbscaled = gdk_pixbuf_scale_simple(pixbuf, w, h, GDK_INTERP_BILINEAR);
   gtk_image_set_from_pixbuf(GTK_IMAGE(image), pxbscaled);
   g_object_unref(pxbscaled);
   g_object_unref(pixbuf);
   return image;
}
