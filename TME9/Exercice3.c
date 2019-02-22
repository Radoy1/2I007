/* Exercice2.c

   A compiler avec :
       gcc `pkg-config --cflags gtk+-2.0` \
          -o Exercice3 Exercice3.c `pkg-config --libs gtk+-2.0`
 */
#include <stdlib.h>
#include <gtk/gtk.h>
#include <string.h>

  
gboolean on_change_normal (GtkRange *range, GtkScrollType scroll,gdouble value, gpointer unite);
gboolean on_change_unite (GtkRange *range, GtkScrollType scroll,gdouble value, gpointer normal);
gboolean on_change_label(GtkRange *range, GtkScrollType scroll,gdouble value, gpointer label);

int main (int argc, char *argv[]) {
  GtkWidget *principale;
  GtkWidget *vbox;
  GtkWidget *label, *normal, *unite;
  gtk_init(&argc, &argv);
  /* ?????????? (2) ?????????? */
  principale = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  vbox       = gtk_vbox_new(TRUE,20);
  label      = gtk_label_new("0");
  normal     = gtk_hscale_new_with_range(0,100,1);
  unite      = gtk_hscale_new_with_range(0,9,1);

  gtk_window_set_title(GTK_WINDOW(principale), "Exercice 3");
  gtk_container_set_border_width(GTK_CONTAINER(principale), 10);
  gtk_container_add(GTK_CONTAINER(principale), vbox);
  g_object_set(vbox, "width-request", 400, "height-request", 200, NULL);
  gtk_container_add(GTK_CONTAINER(vbox), label);
  gtk_container_add(GTK_CONTAINER(vbox), normal);
  gtk_container_add(GTK_CONTAINER(vbox), unite);
  
  gtk_widget_show_all(principale);
  
  
  g_signal_connect(normal,"change-value",G_CALLBACK(on_change_normal),unite);
  g_signal_connect(unite,"change-value",G_CALLBACK(on_change_unite),normal);
  g_signal_connect(normal,"change-value",G_CALLBACK(on_change_label),label);
  g_signal_connect(principale, "delete-event", G_CALLBACK(gtk_main_quit), NULL);
  
  gtk_main ();
  return 0;
}

/* ?????????? (3) ?????????? */
gboolean on_change_normal (GtkRange *range, GtkScrollType scroll,gdouble value,gpointer unite){
  int i;
  i = ((int)value)%10;
  gtk_range_set_value(((GtkRange *)unite),(gdouble)i); 
}
gboolean on_change_unite (GtkRange *range, GtkScrollType scroll,gdouble value,gpointer normal){
  int i;
  i = (int)gtk_range_get_value((GtkRange *)normal)-
    ((int)(gtk_range_get_value((GtkRange *)normal))%10)+(int)value;
  gtk_range_set_value(((GtkRange *)normal),(gdouble)i);

}

gboolean on_change_label(GtkRange *range, GtkScrollType scroll,gdouble value, gpointer label){
  char a[200];
  sprintf(a,"%d",(int)value);
  gtk_label_set_text((GtkLabel *)label,(gchar *)a);
}

