/* Exo1.c */

#include <X11/Xlib.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


Display	             *dpy;           /* le serveur            */
int	              ecran;         /* son ecran par defaut  */
GC                    gc;
Window	              racine, principale, fille[2], menu;
char                 *texte_fille[2] = { "Fille 1", "Fille 2" };
unsigned long         noir, blanc, rouge, vert, bleu;
XEvent	              evmt;
XFontStruct          *font_attributs;
XSetWindowAttributes  window_attributs;


/********** Exo 2 **********/

Window menu;
Bool   dedans;

/********** Fin Exo 2 **********/


/* Les prototypes de fonctions */
void Installer	         (void);
void PourConfigureNotify (XConfigureEvent *evmt);
void PourExpose          (XExposeEvent *evmt);
void largeur_hauteur     (XFontStruct *font_attributs,
		          char *chaine, int *largeur, int *hauteur);

/********** Exo 2 **********/

void PourButtonPress   (XButtonPressedEvent *evmt);
void PourButtonRelease (XButtonReleasedEvent *evmt);

/********** Fin Exo 2 **********/


void largeur_hauteur (XFontStruct *font_attributs,
		      char *chaine, int *largeur, int *hauteur) {

  /* On recupere la largeur de la chaine avec ce font (de ce gc) */
  *largeur = XTextWidth(font_attributs, chaine, strlen(chaine));

  /* Et la hauteur (se dit ascent (haut) et descent (bas)) des caracteres */
  *hauteur = font_attributs->ascent;
}


int main (int argc, char *argv[]) { /* la procedue main()                */
  Installer();
  for (;;) {			    /* la boucle d'evenements            */
    XNextEvent(dpy, &evmt);
    switch (evmt.type) {
      case ConfigureNotify :
	PourConfigureNotify((XConfigureEvent *)(&evmt));
	break;
      case Expose :
	PourExpose((XExposeEvent *)(&evmt));
	break;

	/********** Exo2 **********/
	
      case ButtonPress :
	PourButtonPress((XButtonPressedEvent *)&evmt);
	break;
      case ButtonRelease :
	PourButtonRelease((XButtonReleasedEvent *)&evmt);
	break;
	
	/********** Fin Exo2 **********/
	
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

  /********** Exo 2 **********/

  dedans = True;

  menu = XCreateSimpleWindow(dpy, racine, 0, 0, 200, 100, 1, noir, blanc);
  window_attributs.override_redirect = True;
  XChangeWindowAttributes(dpy, menu, CWOverrideRedirect, &window_attributs);

  XSelectInput(dpy, menu, ButtonPressMask|ButtonReleaseMask|ExposureMask);
  XClearArea(dpy, menu, 0, 0, 200, 100, True);     /* Pour forcer un Expose */

  XSelectInput(dpy, principale,
	       StructureNotifyMask|ButtonPressMask|ButtonReleaseMask|
	       OwnerGrabButtonMask);

  /********** Fin Exo 2 **********/


  XSelectInput(dpy, fille[0], ExposureMask);
  XSelectInput(dpy, fille[1], ExposureMask);

  XStoreName(dpy, principale, "Exercice 2");
  XMapWindow(dpy, principale);
  XMapSubwindows(dpy, principale);
}


void PourConfigureNotify (XConfigureEvent *evmt) {
  int largeur, hauteur;

  largeur = evmt->width;
  hauteur = evmt->height;
  if (dedans) {
    XMoveResizeWindow(dpy, fille[0], 0, 0, largeur/2, hauteur/2);
    XMoveResizeWindow(dpy, fille[1],
		      0, hauteur/2, largeur/2, hauteur - hauteur/2);
  }
}


/********** Exo 2 **********/

void PourExpose (XExposeEvent *evmt) {
  Window        racine;
  int           x, y;
  unsigned int  largeur, hauteur, largeur_bordure, profondeur;
  char         *chaine;
  int           largeur_chaine, hauteur_chaine;

  XGetGeometry(dpy, evmt->window,
	       &racine, &x, &y, &largeur, &hauteur,
	       &largeur_bordure, &profondeur);
  XClearWindow(dpy, evmt->window);

  if (evmt->window == menu) {
    chaine = "Grouper";
    largeur_hauteur(font_attributs, chaine, &largeur_chaine, &hauteur_chaine);
    XDrawString(dpy, evmt->window, gc,
		(largeur - largeur_chaine)/2, (hauteur/2 + hauteur_chaine)/2,
		chaine, strlen(chaine));
    
    XDrawLine(dpy, evmt->window, gc, 0, hauteur/2, largeur, hauteur/2);
    
    chaine = "Degrouper";
    largeur_hauteur(font_attributs, chaine, &largeur_chaine, &hauteur_chaine);
    XDrawString(dpy, evmt->window, gc,
		(largeur - largeur_chaine)/2, (hauteur*3/2 + hauteur_chaine)/2,
		chaine, strlen(chaine));
  } else {
    chaine = texte_fille[evmt->window == fille[0] ? 0 : 1];
    largeur_hauteur(font_attributs, chaine, &largeur_chaine, &hauteur_chaine);
    XDrawString(dpy, evmt->window, gc,
		(largeur - largeur_chaine)/2, (hauteur + hauteur_chaine)/2,
		chaine, strlen(chaine));
  }
}


void PourButtonPress (XButtonPressedEvent *evmt) {
  if (evmt->window == principale) {
    XMoveWindow(dpy, menu, evmt->x_root, evmt->y_root);
    XMapRaised(dpy, menu);
  }
}


void PourButtonRelease (XButtonReleasedEvent *evmt) {
  int           x, y;
  unsigned int  largeur, hauteur, largeur_bordure, profondeur;

  if (evmt->window == menu) {
    if (evmt->x <= 200 && evmt->y <= 50) {          /* partie Grouper   */
      XGetGeometry(dpy, principale,
		   &racine, &x, &y, &largeur, &hauteur,
		   &largeur_bordure, &profondeur);
      XReparentWindow(dpy, fille[0], principale, 0, 0);
      XResizeWindow(dpy, fille[0], largeur/2, hauteur/2);
      XReparentWindow(dpy, fille[1], principale, 0, hauteur/2);
      XResizeWindow(dpy, fille[1], largeur/2, hauteur - hauteur/2);
      dedans = True;
    } else if (evmt->x <= 200 && evmt->y <= 100) {  /* partie Degrouper */
      dedans = False;
      XReparentWindow(dpy, fille[0], racine, 0, 0);
      XReparentWindow(dpy, fille[1], racine, 0, 0);
    }
    XUnmapWindow(dpy, menu);
  }
}

/********** Fin Exo 2 **********/
