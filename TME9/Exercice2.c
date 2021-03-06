/* Exercice2.c

   A compiler avec :
       gcc `pkg-config --cflags gtk+-2.0` \
          -o Exercice2 Exercice2.c `pkg-config --libs gtk+-2.0`
 */

#include <gtk/gtk.h>
#include <cairo.h>
#include <string.h>
#include <stdlib.h>

typedef struct _RVB {
  GtkWidget *planche;
  gint       l, h;
  float      r, v, b;
} *RVB;

gboolean on_change_value (GtkRange *range, GtkScrollType scroll,gdouble value, gpointer rvb);
gboolean on_expose_event(GtkWidget *widget, GdkEventExpose *event, gpointer rvb);
gboolean on_configure_event(GtkWidget *widget, GdkEventConfigure *event, gpointer rvb);
void on_clicked(GtkWidget *widget, gpointer rvb);

int main (int argc, char *argv[]) {
  GtkWidget *principale;
  GtkWidget *vbox1, *vbox2;
  GtkWidget *planche, *rouge, *vert, *bleu, *bouton;
  RVB        rvb;

  gtk_init(&argc, &argv);

  /* creation */
  principale = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  vbox1      = gtk_vbox_new(FALSE, 20);
  vbox2      = gtk_vbox_new(FALSE, 0);
  planche    = gtk_drawing_area_new();
  rouge      = gtk_hscale_new_with_range(0, 255, 1);
  vert       = gtk_hscale_new_with_range(0, 255, 1);
  bleu       = gtk_hscale_new_with_range(0, 255, 1);
  bouton     = gtk_button_new_with_label("Reset");

  /* placement */
  gtk_window_set_title(GTK_WINDOW(principale), "Exercice 2");
  gtk_container_set_border_width(GTK_CONTAINER(principale), 10);
  g_object_set(planche, "width-request", 400, "height-request", 200, NULL);
  gtk_container_add(GTK_CONTAINER(principale), vbox1);
  gtk_container_add(GTK_CONTAINER(vbox1), planche);
  gtk_container_add(GTK_CONTAINER(vbox1), vbox2);
  gtk_container_set_border_width(GTK_CONTAINER(vbox2), 0);
  gtk_container_add(GTK_CONTAINER(vbox2), rouge);
  gtk_container_add(GTK_CONTAINER(vbox2), vert);
  gtk_container_add(GTK_CONTAINER(vbox2), bleu);
  gtk_container_add(GTK_CONTAINER(vbox2), bouton);
  
  g_object_set(planche, "name", "planche", NULL);
  g_object_set(rouge, "name", "rouge", NULL);
  g_object_set(vert, "name", "vert", NULL);
  g_object_set(bleu, "name", "bleu", NULL);

  /* comportement */
  /*
  gtk_widget_set_sensitive(bouton2, FALSE);
  g_signal_connect(bouton1, "clicked", G_CALLBACK(on_clicked), bouton2);
  g_signal_connect(bouton2, "clicked", G_CALLBACK(on_clicked), bouton1);
  */
  
  gtk_widget_show_all(principale);

  rvb = (RVB)malloc(sizeof(struct _RVB));
  rvb->planche = planche;
  rvb->l = 400;
  rvb->h = 200;
  rvb->r = rvb->v = rvb->b = 0.0;
  g_signal_connect(planche, "expose-event", G_CALLBACK(on_expose_event), rvb);
  g_signal_connect(planche, "configure-event", G_CALLBACK(on_configure_event), rvb);
  g_signal_connect(rouge, "change-value", G_CALLBACK(on_change_value), rvb);
  g_signal_connect(vert, "change-value", G_CALLBACK(on_change_value), rvb);
  g_signal_connect(bleu, "change-value", G_CALLBACK(on_change_value), rvb);
  g_signal_connect(bouton, "clicked", G_CALLBACK(on_clicked), rvb);

  g_signal_connect(principale, "delete-event", G_CALLBACK(gtk_main_quit), NULL);
  
  gtk_main ();
  return 0;
}


gboolean on_expose_event(GtkWidget *widget, GdkEventExpose *event, gpointer rvb) {
  gint x, y, width, height;
  cairo_t   *cr;

  if (!strcmp(gtk_widget_get_name(widget), "planche")) {
    cr = gdk_cairo_create(widget->window);
    cairo_set_source_rgb(cr, ((RVB)rvb)->r, ((RVB)rvb)->v, ((RVB)rvb)->b);
    x      = event->area.x;
    y      = event->area.y;
    width  = event->area.width;
    height = event->area.height;
    cairo_rectangle(cr, x, y, width, height); 
    cairo_fill(cr);
  }
  return TRUE;
}


gboolean on_change_value (GtkRange *range, GtkScrollType scroll,
			  gdouble value, gpointer rvb) {
  gint width, height;
  cairo_t   *cr;
  
  if (!strcmp(gtk_widget_get_name(GTK_WIDGET(range)), "rouge")) {
    ((RVB)rvb)->r = value / 255;
  } else if (!strcmp(gtk_widget_get_name(GTK_WIDGET(range)), "vert")) {
    ((RVB)rvb)->v = value / 255;
  } else {
    ((RVB)rvb)->b = value / 255;
  }

  cr = gdk_cairo_create(((RVB)rvb)->planche->window);
  cairo_set_source_rgb(cr, ((RVB)rvb)->r, ((RVB)rvb)->v, ((RVB)rvb)->b);
  width  = ((RVB)rvb)->l;
  height = ((RVB)rvb)->h;
  cairo_rectangle(cr, 0, 0, width, height); 
  cairo_fill(cr);
}


gboolean on_configure_event(GtkWidget *widget, GdkEventConfigure *event,
			    gpointer rvb) {
  ((RVB)rvb)->l = event->width;
  ((RVB)rvb)->h = event->height;
}

void on_clicked(GtkWidget *widget, gpointer rvb){
  gint width,height;
  cairo_t *cr;
  
  ((RVB)rvb)->r=0;
  ((RVB)rvb)->v=0;
  ((RVB)rvb)->b=0;
  
  cr = gdk_cairo_create(((RVB)rvb)->planche->window);
  cairo_set_source_rgb(cr, ((RVB)rvb)->r, ((RVB)rvb)->v, ((RVB)rvb)->b);
  width  = ((RVB)rvb)->l;
  height = ((RVB)rvb)->h;
  cairo_rectangle(cr, 0, 0, width, height); 
  cairo_fill(cr);
}
