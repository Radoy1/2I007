/* Exo1.c */

#include <X11/Xlib.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


Display	      *dpy;			/* le serveur			     */
int	       ecran;			/* son ecran par defaut		     */
GC             gc;
Window	       racine, principale, fille[2], menu;
char          *texte_fille[2] = { "Fille 1", "Fille 2" };
unsigned long  noir, blanc, rouge, vert, bleu;
XEvent	       evmt;
XFontStruct   *font_attributs;


/********** (1) **********/


/* Les prototypes de fonctions */
void Installer	         (void);
void largeur_hauteur     (XFontStruct *font_attributs,
		          char *chaine, int *largeur, int *hauteur);
void PourConfigureNotify (XConfigureEvent *evmt);
void PourExposeEvent(XExposeEvent *evmt);
/********** (2) **********/

int main (int argc, char *argv[]) { /* la procedue main()                */
  Installer();
  for (;;) {			    /* la boucle d'evenements            */
    XNextEvent(dpy, &evmt);
    switch (evmt.type) {

    case ConfigureNotify:
      PourConfigureNotify((XConfigureEvent *)&evmt);
      break;
    case Expose:
      PourExposeEvent((XExposeEvent *)&evmt);
      break;

      default :;
    }
  }
}


void Installer (void) {
  dpy            = XOpenDisplay(NULL);
  racine         = DefaultRootWindow(dpy);
  ecran          = DefaultScreen(dpy);
  gc             = DefaultGC(dpy, ecran);

  /* N'hesiter pas a utiliser la commande xfontsel pour choisir un font. */
  font_attributs = XLoadQueryFont(dpy,"-adobe-times-*-i-*-*-25-*-*-*-*-*-*-*");

  XSetFont(dpy, gc, font_attributs->fid);

  /* ne fonctionne que si le serveur est en TrueColor ou DirectColor.
     Sinon, il faut s'adresser a la table de couleur Colormap du serveur */
  noir  = 0x0;
  blanc = 0xFFFFFF;
  rouge = 0xFF0000;
  vert  = 0x00FF00;
  bleu  = 0x0000FF;

  principale = XCreateSimpleWindow(dpy, racine, 0, 0, 200, 200, 0,
                 noir, blanc);
  fille[0]   = XCreateSimpleWindow(dpy, principale, 0, 0, 100, 100, 1,
                 noir, rouge);
  fille[1]   = XCreateSimpleWindow(dpy, principale, 0, 100, 100, 100, 1,
                 noir, vert);

  /********** (4) **********/
  XSelectInput(dpy, principale, StructureNotifyMask);
  XSelectInput(dpy, fille[0], ExposureMask);
  XSelectInput(dpy, fille[1], ExposureMask);

  XStoreName(dpy, principale, "Exercice 1");
  XMapWindow(dpy, principale);
  XMapSubwindows(dpy, principale);
}


void largeur_hauteur (XFontStruct *font_attributs,
		      char *chaine, int *largeur, int *hauteur) {

  /* On recupere la largeur de la chaine avec ce font (de ce gc) */
  *largeur = XTextWidth(font_attributs, chaine, strlen(chaine));

  /* Et la hauteur (se dit ascent (haut) et descent (bas)) des caracteres */
  *hauteur = font_attributs->ascent;
}

void PourConfigureNotify(XConfigureEvent *evmt){

  XMoveResizeWindow(dpy, fille[1], 0, 0, evmt -> width/2, evmt -> height/2); 
  XMoveResizeWindow(dpy, fille[0], 0, evmt -> height/2, evmt -> width/2,
		    evmt -> height);
}


void PourExposeEvent(XExposeEvent *evmt){
  XClearWindow(dpy, fille[0]);
  XClearWindow(dpy, fille[1]);
  XDrawString(dpy, fille[0], gc, 25, 25, "Fille 1", 7);
  XDrawString(dpy, fille[1], gc, 25, 25, "Fille 0", 7);
}
