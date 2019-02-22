/* Exercice2.c

   A compiler avec :
       gcc `pkg-config --cflags gtk+-2.0` \
          -o Exercice1_xor Exercice1_xor.c `pkg-config --libs gtk+-2.0` -lX11
 */

#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <cairo.h>


#include <X11/Xlib.h>
#include <gdk/gdkx.h>
#include <cairo/cairo-xlib.h>


gboolean on_expose_event(GtkWidget *widget, GdkEventExpose *event,
			 gpointer data);
gboolean on_button_press_event(GtkWidget *widget, GdkEventButton *event,
			       gpointer data);
gboolean on_button_release_event(GtkWidget *widget, GdkEventButton *event,
				 gpointer data);
gboolean on_button_motion_event(GtkWidget *widget, GdkEventButton *event,
				gpointer data);
gboolean on_configure_event(GtkWidget *widget, GdkEventConfigure *event,
			    gpointer data);


GtkWidget *principale;
GtkWidget *planche;
cairo_t   *cr;
gdouble    x_debut, y_debut, x_courant, y_courant, x_fin, y_fin;

Display  *dpy;
Window    fen;
GC        gc_xor;;



int main (int argc, char *argv[]) {
  XGCValues gc_val;

  gtk_init(&argc, &argv);

  principale = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  planche    = gtk_drawing_area_new();

  gtk_window_set_title(GTK_WINDOW(principale), "Exercice 1 - X11 - xor");
  gtk_container_set_border_width(GTK_CONTAINER(principale), 10);
  
  g_object_set(planche, "width-request", 400, "height-request", 200,
	       "events",
	       GDK_BUTTON_PRESS_MASK|GDK_BUTTON_RELEASE_MASK|
	          GDK_BUTTON_MOTION_MASK,
	       NULL);
  gtk_container_add(GTK_CONTAINER(principale), planche);

  g_signal_connect(planche, "expose-event", G_CALLBACK(on_expose_event), NULL);
  g_signal_connect(planche,
    "button-press-event", G_CALLBACK(on_button_press_event), NULL);
  g_signal_connect(planche,
    "button-release-event", G_CALLBACK(on_button_release_event), NULL);
  g_signal_connect(planche,
    "motion-notify-event", G_CALLBACK(on_button_motion_event), NULL);
  g_signal_connect(principale,
		   "delete-event", G_CALLBACK(gtk_main_quit), NULL);
  g_signal_connect(principale,
		   "configure-event", G_CALLBACK(on_configure_event), NULL);
  gtk_widget_show_all(principale);

  dpy    = gdk_x11_display_get_xdisplay(gdk_display_get_default());
  fen    = gdk_x11_drawable_get_xid(gtk_widget_get_window (planche));

  gc_val.function = GXxor;
  gc_val.foreground = 0xffffff;
  gc_xor = XCreateGC(dpy, fen, GCFunction|GCForeground, &gc_val);

  gtk_main ();
  return 0;
}


gboolean on_expose_event(GtkWidget *widget, GdkEventExpose *event,
			 gpointer data) {
  cairo_t     *cr;

  GdkDrawable *d = gtk_widget_get_window(widget); /* ou widget->window */
  gint         width, height;
  
  cr = gdk_cairo_create(d);               /* contexte (avec sa surface) */
  cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);/* choix de la source : violet uni */
  gtk_widget_get_size_request (widget, &width, &height);
  cairo_rectangle(cr, 0, 0, width, height);    /* un chemin rectangulaire */
  cairo_fill(cr);                         /* peindre le chemin (interieur) */  
  return TRUE;
}


gboolean on_button_press_event(GtkWidget *widget, GdkEventButton *event,
			       gpointer data) {
  GdkDrawable *d  = gtk_widget_get_window(widget);
  cairo_t     *cr = gdk_cairo_create(d);
  
  x_debut = x_courant = x_fin = event->x;
  y_debut = y_courant = y_fin = event->y;

  XDrawLine(dpy, fen, gc_xor, x_debut, y_debut, x_courant, y_courant);

  return TRUE;
}


gboolean on_button_motion_event(GtkWidget *widget, GdkEventButton *event,
			       gpointer data) {
  GdkDrawable *d  = gtk_widget_get_window(widget);
  cairo_t     *cr = gdk_cairo_create(d);
  
  XDrawLine(dpy, fen, gc_xor, x_debut, y_debut, x_courant, y_courant);
  x_courant = event->x;
  y_courant = event->y;
  XDrawLine(dpy, fen, gc_xor, x_debut, y_debut, x_courant, y_courant);

  return TRUE;
}


gboolean on_button_release_event(GtkWidget *widget, GdkEventButton *event,
				gpointer data) {
  GdkDrawable *d  = gtk_widget_get_window(widget);
  cairo_t     *cr = gdk_cairo_create(d);

  x_fin = event->x;
  y_fin = event->y;

  cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);	/* choix de la source : noir */
  cairo_move_to(cr, x_debut, y_debut);
  cairo_line_to(cr, x_fin, y_fin);
  cairo_stroke(cr);

  return TRUE;
}


gboolean on_configure_event(GtkWidget *widget, GdkEventConfigure *event,
			    gpointer data) {

  gtk_widget_set_size_request(planche, event->width - 25, event->height - 25);

  return FALSE;		/* Attention : TRUE ==> principale ne change pas */
}
