/* Exercice2.c

   A compiler avec :
       gcc `pkg-config --cflags gtk+-2.0` \
          -o Exercice1 Exercice1.c `pkg-config --libs gtk+-2.0`
 */

#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <cairo.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <X11/Xlib.h>

enum Forme { TRAIT, RECTANGLE, ELLIPSE };

typedef struct _Trait {
  enum Forme forme;
  double dx, dy, fx, fy;
  double rouge, vert, bleu;
  double epaisseur;
} Trait;

typedef struct _Rectangle {
  enum Forme forme;
  double dx, dy, fx, fy;
  double rouge, vert, bleu;
  double epaisseur;
} Rectangle;


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
void on_activate (GtkMenuItem *menu_item, gpointer data);


GtkWidget *principale;
GtkWidget *planche;
cairo_t   *cr;
gdouble    x_debut, y_debut, x_courant, y_courant, x_fin, y_fin;

GtkWidget *color_dialog, *color_selection;
GtkWidget *entree_dialog, *entree, *vbox;

GtkWidget *layout, *menu_bar, *fmenu, *emenu, *fomenu;
GtkWidget *menu_item;

Trait     *tableau_traits[200];
int        nb_traits;
double     epaisseur, rouge, vert, bleu;

Display *dpy;
Window   fen;
GC       gc_xor;
enum Forme    forme;


int main (int argc, char *argv[]) {
  XGCValues gc_val;
  
  gtk_init(&argc, &argv);

  principale = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  layout     = gtk_layout_new(NULL, NULL);
  planche    = gtk_drawing_area_new();
  menu_bar   = gtk_menu_bar_new();
  fmenu      = gtk_menu_new();
  emenu      = gtk_menu_new();
  fomenu     = gtk_menu_new();
  forme      = TRAIT;
  
  gtk_window_set_title(GTK_WINDOW(principale), "Exercice 1");
  gtk_container_set_border_width(GTK_CONTAINER(principale), 10);
  g_object_set(planche, "width-request", 400, "height-request", 200,
	       "events",
	       GDK_BUTTON_PRESS_MASK|GDK_BUTTON_RELEASE_MASK|
	       GDK_BUTTON_MOTION_MASK,
	          gtk_widget_get_events (planche),
	       NULL);

  gtk_container_add(GTK_CONTAINER(principale), layout);
  gtk_widget_set_size_request(layout, 400, 250);

  
  /********** Les menus **********/

  menu_item = gtk_menu_item_new_with_label("Nouveau");
  gtk_menu_shell_append(GTK_MENU_SHELL(fmenu), menu_item);
  g_object_set(menu_item, "name", "Nouveau", NULL);
  g_signal_connect(menu_item, "activate", G_CALLBACK(on_activate), NULL);
  
  menu_item = gtk_menu_item_new_with_label("Quitter");
  gtk_menu_shell_append(GTK_MENU_SHELL(fmenu), menu_item);
  g_object_set(menu_item, "name", "Quitter", NULL);
  g_signal_connect(menu_item, "activate", G_CALLBACK(on_activate), NULL);
  
  menu_item = gtk_menu_item_new_with_label("Fichier");
  g_object_set(menu_item, "name", "Fichier", NULL);
  gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), menu_item);
  g_signal_connect(menu_item, "activate", G_CALLBACK(on_activate), NULL);

  gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_item), fmenu);

  menu_item = gtk_menu_item_new_with_label("Couleur");
  gtk_menu_shell_append(GTK_MENU_SHELL(emenu), menu_item);
  g_object_set(menu_item, "name", "Couleur", NULL);
  g_signal_connect(menu_item, "activate", G_CALLBACK(on_activate), NULL);
  
  menu_item = gtk_menu_item_new_with_label("Epaisseur");
  gtk_menu_shell_append(GTK_MENU_SHELL(emenu), menu_item);
  g_object_set(menu_item, "name", "Epaisseur", NULL);
  g_signal_connect(menu_item, "activate", G_CALLBACK(on_activate), NULL);
  
  menu_item = gtk_menu_item_new_with_label("Edit");
  g_object_set(menu_item, "name", "Edit", NULL);
  gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), menu_item);
  g_signal_connect(menu_item, "activate", G_CALLBACK(on_activate), NULL);

  gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_item), emenu);

  menu_item = gtk_menu_item_new_with_label("Trait");
  gtk_menu_shell_append(GTK_MENU_SHELL(fomenu), menu_item);
  g_object_set(menu_item, "name", "Trait",NULL);
  g_signal_connect(menu_item, "activate", G_CALLBACK(on_activate), NULL);

  menu_item = gtk_menu_item_new_with_label("Rectangle");
  gtk_menu_shell_append(GTK_MENU_SHELL(fomenu), menu_item);
  g_object_set(menu_item, "name", "Rectangle",NULL);
  g_signal_connect(menu_item, "activate", G_CALLBACK(on_activate), NULL);

  menu_item = gtk_menu_item_new_with_label("Ellipse");
  gtk_menu_shell_append(GTK_MENU_SHELL(fomenu), menu_item);
  g_object_set(menu_item, "name", "Ellipse",NULL);
  g_signal_connect(menu_item, "activate", G_CALLBACK(on_activate), NULL);
  
  menu_item = gtk_menu_item_new_with_label("Forme");
  gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), menu_item);
  g_object_set(menu_item, "name", "Forme",NULL);
  g_signal_connect(menu_item, "activate", G_CALLBACK(on_activate), NULL);
  
  gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_item), fomenu);
  
  gtk_widget_show_all(menu_bar);
  gtk_widget_show_all(fmenu);
  gtk_widget_show_all(emenu);
  gtk_widget_show_all(fomenu);
  
  /********** Mettre en place les composantes et les connections **********/
  
  gtk_layout_put((GtkLayout *)layout, menu_bar, 0, 0);
  gtk_layout_put((GtkLayout *)layout, planche, 0, 40);

  g_signal_connect(planche,
		   "expose-event", G_CALLBACK(on_expose_event), NULL);
  g_signal_connect(planche,
    "button-press-event", G_CALLBACK(on_button_press_event), NULL);
  g_signal_connect(planche,
    "button-release-event", G_CALLBACK(on_button_release_event), NULL);
  g_signal_connect(planche,
    "motion-notify-event", G_CALLBACK(on_button_motion_event), NULL);
  g_signal_connect(principale,
		   "configure-event", G_CALLBACK(on_configure_event), NULL);
  g_signal_connect(principale,
		   "delete-event", G_CALLBACK(gtk_main_quit), NULL);

  gtk_widget_show_all(layout);
  gtk_widget_show(planche);
  gtk_widget_show_all(principale);

  /**********    Xlib       **********/

  dpy = gdk_x11_display_get_xdisplay(gdk_display_get_default());
  fen = gdk_x11_drawable_get_xid(gtk_widget_get_window(planche));

  
  /********** Les dialogues **********/

  color_dialog    = gtk_color_selection_dialog_new ("Choix de couleur");
  color_selection = gtk_color_selection_dialog_get_color_selection(
		      (GtkColorSelectionDialog *)color_dialog);

  entree = gtk_entry_new();
  gtk_entry_set_text((GtkEntry *)entree, "          ");
  gtk_widget_show_all(entree);
  entree_dialog = gtk_dialog_new_with_buttons ("Epaisseur Dialogue",
		     (GtkWindow *)principale,
		     GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                     GTK_STOCK_OK,
		     GTK_STOCK_CANCEL,
		     NULL);
  vbox = gtk_dialog_get_content_area((GtkDialog *)entree_dialog);
  gtk_box_pack_start((GtkBox *)vbox, entree, FALSE, FALSE, 5);

  nb_traits = 0;
  epaisseur = 1;
  rouge     = vert = bleu = 0;
  
  gc_val.function = GXxor;
  gc_val.foreground = 0xffffff;
  gc_xor = XCreateGC(dpy, fen, GCFunction|GCForeground, &gc_val);

  gtk_main ();
  return 0;
}


gboolean on_expose_event(GtkWidget *widget, GdkEventExpose *event,
			 gpointer data) {
  cairo_t *cr;
  int      i;

  GdkDrawable *d = gtk_widget_get_window(widget); /* ou widget->window */
  gint         width, height;
  
  cr = gdk_cairo_create(d);               /* contexte (avec sa surface) */
  cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);/* choix de la source */
  gtk_widget_get_size_request (widget, &width, &height);
  cairo_rectangle(cr, 0, 0, width, height);    /* un chemin rectangulaire */
  cairo_fill(cr);                         /* peindre le chemin (interieur) */

  for (i = 0; i < nb_traits; ++i) {
    Trait *t;
    t = tableau_traits[i];
    
    switch (t->forme){
    case TRAIT:
      cairo_set_source_rgb(cr, t->rouge, t->vert, t->bleu);
      cairo_set_line_width(cr, t->epaisseur);
      cairo_move_to(cr, t->dx, t->dy);
      cairo_line_to(cr, t->fx, t->fy);
      cairo_stroke(cr);
      break;
    case RECTANGLE:
      cairo_set_source_rgb(cr, t->rouge, t->vert, t->bleu);
      cairo_set_line_width(cr, t->epaisseur);
      cairo_move_to(cr, t->dx, t->dy);
      cairo_rectangle(cr, t->dx, t->dy, t->fx - t->dx, t->fy - t->dy);
      cairo_stroke(cr);
      break;
    default:;
    }
  }
  return TRUE;
}


gboolean on_button_press_event(GtkWidget *widget, GdkEventButton *event,
			       gpointer data) {
  x_debut = x_fin = x_courant = event->x;
  y_debut = y_fin = y_courant = event->y;

  switch (forme){
  case TRAIT:
    XDrawLine(dpy, fen, gc_xor, x_debut, y_debut, x_courant, y_courant);
    break;
  case RECTANGLE:
    XDrawRectangle(dpy, fen, gc_xor, x_debut, y_debut, x_courant - x_debut , y_courant - y_debut);
    break;
  case ELLIPSE:
    XDrawArc(dpy, fen, gc_xor, x_debut, y_debut,  x_courant - x_debut, y_courant - y_debut,
	     0, 360*64);
  default:;
  }
  
  return TRUE;
}


gboolean on_button_release_event(GtkWidget *widget, GdkEventButton *event,
				gpointer data) {
  GdkDrawable *d  = gtk_widget_get_window(widget);
  cairo_t     *cr = gdk_cairo_create(d);
  Trait       *t  = (Trait *)malloc(sizeof(struct _Trait));

  x_fin = event->x;
  y_fin = event->y;

  switch (forme){
  case TRAIT:
    cairo_set_source_rgb(cr, rouge, vert, bleu);
    cairo_set_line_width(cr, epaisseur);
    cairo_move_to(cr, x_debut, y_debut);
    cairo_line_to(cr, x_fin, y_fin);
    cairo_stroke(cr);

    tableau_traits[nb_traits++] = t;
    t->forme = TRAIT;
    t->dx        = x_debut;
    t->dy        = y_debut;
    t->fx        = x_fin;
    t->fy        = y_fin;
    t->epaisseur = epaisseur;
    t->rouge     = rouge;
    t->vert      = vert;
    t->bleu      = bleu;
    break;
  case RECTANGLE:
    cairo_set_source_rgb(cr, rouge, vert, bleu);
    cairo_set_line_width(cr, epaisseur);
    cairo_move_to(cr, x_debut, y_debut);
    cairo_rectangle(cr, x_debut, y_debut, x_fin - x_debut, y_fin - y_debut);
    cairo_stroke(cr);

    tableau_traits[nb_traits++] = t;
    t->forme = RECTANGLE;
    t->dx        = x_debut;
    t->dy        = y_debut;
    t->fx        = x_fin;
    t->fy        = y_fin;
    t->epaisseur = epaisseur;
    t->rouge     = rouge;
    t->vert      = vert;
    t->bleu      = bleu;
    break;
  case ELLIPSE:
    cairo_set_source_rgb(cr, rouge, vert, bleu);
    cairo_set_line_width(cr, epaisseur);
    cairo_move_to(cr, x_debut, y_debut);
    cairo_arc(cr,  (x_debut+x_fin)/2.0, (y_debut+y_fin)/2.0, (x_fin-y_fin)/2.0,
	      0.0, 64);
    cairo_stroke(cr);

    tableau_traits[nb_traits++] = t;
    t->forme = ELLIPSE;
    t->dx        = x_debut;
    t->dy        = y_debut;
    t->fx        = x_fin;
    t->fy        = y_fin;
    t->epaisseur = epaisseur;
    t->rouge     = rouge;
    t->vert      = vert;
    t->bleu      = bleu;
  default:;
  }
  
  return TRUE;
}


gboolean on_configure_event(GtkWidget *widget, GdkEventConfigure *event,
			    gpointer data) {

  gtk_widget_set_size_request(planche, event->width - 20, event->height - 20);
  gtk_widget_set_size_request(menu_bar, event->width - 25, 30);

  return FALSE;
}

gboolean on_button_motion_event(GtkWidget *widget, GdkEventButton *event,
			       gpointer data) {
  GdkDrawable *d  = gtk_widget_get_window(widget);
  cairo_t     *cr = gdk_cairo_create(d);
  
  switch (forme){
  case TRAIT:
    XDrawLine(dpy, fen, gc_xor, x_debut, y_debut, x_courant, y_courant);
    break;
  case RECTANGLE:
    XDrawRectangle(dpy, fen, gc_xor, x_debut, y_debut, x_courant - x_debut , y_courant - y_debut);
    break;
  default:;
  }
  
  x_courant = event->x;
  y_courant = event->y;
  
  switch (forme){
  case TRAIT:
    XDrawLine(dpy, fen, gc_xor, x_debut, y_debut, x_courant, y_courant);
    break;
  case RECTANGLE:
    XDrawRectangle(dpy, fen, gc_xor, x_debut, y_debut, x_courant - x_debut , y_courant - y_debut);
    break;
  default:;
  }
  return TRUE;
}

void on_activate (GtkMenuItem *menu_item, gpointer data) {
  char     *chaine = strdup(gtk_widget_get_name(GTK_WIDGET(menu_item)));
  GdkColor  color;
  gint      reponse;
  char      texte[200];
				     
  if (!strcmp(chaine, "Couleur")) {
    reponse = gtk_dialog_run (GTK_DIALOG (color_dialog));
    gtk_color_selection_get_current_color (
      (GtkColorSelection *)color_selection, &color);
    gtk_widget_hide(color_dialog);
    rouge = color.red/65535.0;      /* 2 ^ 16 */
    vert  = color.green/65535.0;
    bleu  = color.blue/65535.0;
  } else if (!strcmp(chaine, "Epaisseur")) {
    sprintf(texte, "%d", (int)epaisseur);
    gtk_entry_set_text((GtkEntry *)entree, texte);
    reponse = gtk_dialog_run (GTK_DIALOG (entree_dialog));
    gtk_widget_hide(entree_dialog);
    printf("%s\n", gtk_entry_get_text((GtkEntry *)entree));
    epaisseur = atoi(gtk_entry_get_text((GtkEntry *)entree));
    printf("%lf\n", epaisseur);

  } else if(!strcmp(chaine, "Trait")){
    forme = TRAIT;
    
  }else if(!strcmp(chaine, "Rectangle")){
    forme = RECTANGLE;

  }else if(!strcmp(chaine, "Ellipse")){
    forme = ELLIPSE;
    
  }
  

}
