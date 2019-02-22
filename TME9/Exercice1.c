/* Exercice1.c

   A compiler avec :
       gcc `pkg-config --cflags gtk+-2.0` \
          -o Exercice1 Exercice1.c `pkg-config --libs gtk+-2.0`
 */

#include <gtk/gtk.h>
#include <string.h>


void on_clicked (GtkWidget *widget, gpointer lautre);


int main (int argc, char *argv[]) {
  GtkWidget *principale;
  GtkWidget *hbox;
  GtkWidget *bouton1, *bouton2;

  gtk_init(&argc, &argv);

  /* creation */
  principale = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  hbox       = gtk_hbox_new(TRUE, 20);
  bouton1    = gtk_button_new_with_label("Bouton 1");
  bouton2    = gtk_button_new_with_label("Bouton 2");

  /* placement */
  gtk_window_set_title(GTK_WINDOW(principale), "Exercice 1");
  gtk_container_set_border_width(GTK_CONTAINER(principale), 10);
  gtk_container_add(GTK_CONTAINER(principale), hbox);
  gtk_container_add(GTK_CONTAINER(hbox), bouton1);
  gtk_container_add(GTK_CONTAINER(hbox), bouton2);

  /* comportement */
  gtk_widget_set_sensitive(bouton2, FALSE);
  g_signal_connect(bouton1, "clicked", G_CALLBACK(on_clicked), bouton2);
  g_signal_connect(bouton2, "clicked", G_CALLBACK(on_clicked), bouton1);
  gtk_widget_show_all(principale);

  g_signal_connect(principale, "delete-event",
		   G_CALLBACK(gtk_main_quit), NULL);

  gtk_main ();
  return 0;
}


void on_clicked (GtkWidget *widget, gpointer lautre) {
  static int nb = 0;

  if (!strcmp("Bouton 1", gtk_button_get_label(GTK_BUTTON(widget)))) {
    if (nb == 9) {
      gtk_main_quit();
    } else {
      nb++;
    }
  }
  gtk_widget_set_sensitive(lautre, TRUE);
  gtk_widget_set_sensitive(widget, FALSE);
}
