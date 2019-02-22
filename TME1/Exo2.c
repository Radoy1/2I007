/* Exo2.c */

#include <X11/Xlib.h>
#include <stdlib.h>
#include <stdio.h>

#define min(x, y)	((x) < (y) ? (x) : (y))
#define max(x, y)	((x) > (y) ? (x) : (y))
#define abs(x)		((x) > 0 ? (x) : -(x))


Display	      *dpy;
int	       ecran;
Window	       racine, principale, fille;
XEvent	       evmt;
unsigned long  noir, blanc;
double         largeur_principale, hauteur_principale;
double         x_fille, y_fille, largeur_fille,hauteur_fille;
int	       bouton;

int	       x, y, nb;


/* Les prototypes de fonctions */
void Installer	         (void);
void PourButtonPress     (XButtonEvent *evmt);
void PourMotionNotify    (XPointerMovedEvent *evmt);
void PourButtonRelease   (XButtonEvent *evmt);
void PourConfigureNotify (XConfigureEvent *evmt);


int main (int argc, char *argv[]) {	/* la procedue main()                */
  Installer();
  for (;;) {				/* la boucle d'evenements            */
      XNextEvent(dpy, &evmt);
      switch (evmt.type) {
        case ButtonPress :
	  PourButtonPress((XButtonEvent *)(&evmt));
	  break;
        case MotionNotify :
	  PourMotionNotify((XPointerMovedEvent *)(&evmt));
	  break;
        case ButtonRelease :
	  PourButtonRelease((XButtonEvent *)(&evmt));
	  break;
        case ConfigureNotify :
	  PourConfigureNotify((XConfigureEvent *)(&evmt));
	  break;
        default :;
      }
  }
}


void Installer (void) {
  dpy    = XOpenDisplay(NULL);
  racine = DefaultRootWindow(dpy);
  ecran  = DefaultScreen(dpy);
  noir   = 0x0;
  blanc  = 0xFFFFFF;

  x = y = bouton = -1;
  nb = 0;

  largeur_principale = hauteur_principale = 200;

  largeur_fille = largeur_principale / 10;
  hauteur_fille = hauteur_principale / 10;
  x_fille       = (largeur_principale - largeur_fille) * 0.5;
  y_fille       = (hauteur_principale - hauteur_fille) * 0.5;

  principale = XCreateSimpleWindow(dpy,
				   racine,
				   0, 0,
				   largeur_principale,
				   hauteur_principale,
				   0,
				   noir, blanc);
  fille      = XCreateSimpleWindow(dpy,
				   principale,
				   x_fille,
				   y_fille,
				   largeur_fille, hauteur_fille,
				   1,
				   noir, noir);

  XStoreName(dpy, principale, "Exercice 3");
  XSelectInput(dpy,
	       principale,
	       ButtonPressMask|ButtonMotionMask|ButtonReleaseMask
	         |StructureNotifyMask);

  XMapSubwindows(dpy, principale);
  XMapWindow(dpy, principale);
}


void PourButtonPress (XButtonEvent *evmt) {
  if (!nb) {
    bouton = evmt->button;
    if (evmt->subwindow == fille) {
      x = evmt->x - x_fille;
      y = evmt->y - y_fille;
    }
  }
  nb++;
}


void PourMotionNotify (XPointerMovedEvent *evmt) {
  if (x >= 0) {
    x_fille = max(0, evmt->x - x);
    x_fille = min(x_fille, largeur_principale - largeur_fille);
    y_fille = max(0, evmt->y - y);
    y_fille = min(y_fille, hauteur_principale - hauteur_fille);

    XMoveWindow(dpy, fille, x_fille, y_fille);

    /*****

	  Si on souhaite utiliser une procedure traitant d'une maniere
	  generale les attributs concernant une fenetre pour la deplacer.

      XWindowChanges attributes;

      attributes.x = x_fille;
      attributes.y = y_fille;

      XConfigureWindow(dpy,
		       fille,
		       CWX|CWY,
		       &attributes);

    *****/
  }
}


void PourButtonRelease (XButtonEvent *evmt) {
  if (evmt->button == bouton) {
    x = y = bouton = -1;
  }
  nb--;
}


void PourConfigureNotify (XConfigureEvent *evmt) {
  XWindowChanges attributes;

  attributes.width  = largeur_fille = evmt->width / 10.0;
  attributes.height = hauteur_fille = evmt->height / 10.0;
  attributes.x      = x_fille = x_fille * evmt->width / largeur_principale;
  attributes.y      = y_fille = y_fille * evmt->height / hauteur_principale;

  largeur_principale = evmt->width;
  hauteur_principale = evmt->height;

  XConfigureWindow(dpy,
		   fille,
		   CWX|CWY|CWWidth|CWHeight,
		   &attributes);

  /*****

	Pour avoir la meme chose en utilisant les utilitaires XResizeWindow()
	et XMoveWindow(). En deux coups, donc plus cher.

  largeur_fille      = evmt->width / 10.0;
  hauteur_fille      = evmt->height / 10.0;
  x_fille            = x_fille * evmt->width / largeur_principale;
  y_fille            = y_fille * evmt->height / hauteur_principale;
  largeur_principale = evmt->width;
  hauteur_principale = evmt->height;

  XResizeWindow(dpy, fille, largeur_fille, hauteur_fille);
  XMoveWindow(dpy, fille, x_fille, y_fille);

  *****/
}
