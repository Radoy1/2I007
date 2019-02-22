/* Exo1.canvas */

#include <X11/Xlib.h>
#include <stdlib.h>
#include <stdio.h>

#define min(x, y)	((x) < (y) ? (x) : (y))
#define max(x, y)	((x) > (y) ? (x) : (y))
#define abs(x)		((x) > 0 ? (x) : -(x))

/*****

      xc, yc, lc, hc du curseur
      L, H de la principale

      (xc / (L - lc)) == (indice_curseur / max_indice)
      yc              == 0

      avec comme choix lc = hc = H

Pour dessiner un rectangle plein :

XFillRectangle(serveur,
               fenetre,
	       contexte_graphique,
	       x, y,
	       largeur, hauteur);

avec par exemple :

     - dpy			comme serveur
     - reglettre->fenetre	comme fenetre
     - DefaultGC(dpy, ecran)	comme contexte graphique (c'est l'outil pour
       		      		dessiner avec comme couleur par defaut le noir)

*****/

typedef struct _REGLETTE {
  Window fenetre;
  int    largeur, hauteur;
  int    indice_curseur;
  int    max_indice;
  int    couleur_curseur;
  int	 bouton;
  int    x_bouton, y_bouton;
  int    nb;			/* pour enregistrer le nombre de bouton deja
				   enfonce */
} *REGLETTE;


Display	      *dpy;
int	       ecran;
Window	       racine;
unsigned long  noir, blanc;
XEvent	       evmt;
REGLETTE      reglette;

/* Les prototypes de fonctions */
void Installer	         (void);
REGLETTE CreerReglette	 (Display *dpy,
			  Window mere,
			  int x, int y,
			  int largeur, int hauteur,
			  int indice_curseur,
			  int max_indice,
			  int couleur);
void RaffraichirReglette (REGLETTE reglette);
void PourButtonPressReglette (REGLETTE reglette, XButtonEvent *evmt);
void PourMotionNotifyReglette (REGLETTE reglette, XPointerMovedEvent *evmt);
void PourButtonReleaseReglette (REGLETTE reglette, XButtonEvent *evmt);
void PourConfigureNotifyReglette (REGLETTE reglette, XConfigureEvent *evmt);
void PourExposeReglette (REGLETTE reglette, XExposeEvent *evmt);
void PourButtonPress     (XButtonEvent *evmt);
void PourMotionNotify    (XPointerMovedEvent *evmt);
void PourButtonRelease   (XButtonEvent *evmt);
void PourConfigureNotify (XConfigureEvent *evmt);
void PourExpose		 (XExposeEvent *evmt);


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
        case Expose :
	  PourExpose((XExposeEvent *)(&evmt));
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

  reglette = CreerReglette(dpy, racine, 0, 0, 200, 20, 0, 255, blanc);

  XStoreName(dpy, reglette->fenetre, "Exercice 2");

  XMapWindow(dpy, reglette->fenetre);
}


REGLETTE CreerReglette(Display *dpy,
		       Window mere,
		       int x, int y,
		       int largeur, int hauteur,
		       int indice_curseur,
		       int max_indice,
		       int couleur) {

  REGLETTE aux = (REGLETTE)(malloc(sizeof(struct _REGLETTE)));

  aux->fenetre = XCreateSimpleWindow(dpy, mere, x, y, largeur, hauteur, 1,
				     noir, couleur);
  aux->largeur         = largeur;
  aux->hauteur         = hauteur;
  aux->indice_curseur  = min(indice_curseur, max_indice);
  aux->max_indice      = max_indice;
  aux->couleur_curseur = couleur;
  aux->bouton          = aux->x_bouton = aux->y_bouton = -1;
  aux->nb              = 0;

  XSelectInput(dpy,aux->fenetre,ButtonReleaseMask|ButtonPressMask|ButtonMotionMask|StructureNotifyMask|ExposureMask);
  
  return aux;
}


void RaffraichirReglette (REGLETTE reglette) {
  int xc, yc, lc, hc;			/* du curseur */

  lc = hc = reglette->hauteur;
  xc = reglette->indice_curseur * (reglette->largeur - lc)
         / reglette->max_indice;
  yc = 0;
  
  XClearWindow(dpy,reglette->fenetre);
  XFillRectangle(dpy,reglette->fenetre,DefaultGC(dpy,ecran),xc,yc,lc,hc);
  
}


void PourButtonPressReglette (REGLETTE reglette, XButtonEvent *evmt) {
  if (!reglette->nb) {
    int xc, yc, lc, hc;			/* du curseur */

    lc = hc = reglette->hauteur;
    xc = reglette->indice_curseur * (reglette->largeur - lc)
           / reglette->max_indice;
    yc = 0;

    /********** ?????????? **********/

  }

  /********** ?????????? **********/
}


void PourMotionNotifyReglette (REGLETTE reglette, XPointerMovedEvent *evmt) {
  int xc, yc, lc, hc;


  /********** ?????????? **********/

    lc = hc = reglette->hauteur;
    xc = max(0, evmt->x - reglette->x_bouton);
    xc = min(xc, reglette->largeur - lc);
    yc = max(0, evmt->y - reglette->y_bouton);
    yc = min(yc, reglette->hauteur - hc);
    reglette->indice_curseur = xc * reglette->max_indice
	                         / (reglette->largeur - lc);

  /********** ?????????? **********/

}


void PourButtonReleaseReglette (REGLETTE reglette, XButtonEvent *evmt) {
  if (evmt->button == reglette->bouton) {
    int xc, yc, lc, hc;			/* du curseur */

    lc = hc = reglette->hauteur;
    xc = reglette->indice_curseur * (reglette->largeur - lc)
           / reglette->max_indice;
    yc = 0;

    /********** ?????????? **********/

  }

  /********** ?????????? **********/

}


void PourConfigureNotifyReglette (REGLETTE reglette, XConfigureEvent *evmt) {
  XWindowChanges attributes;

  /********** ?????????? **********/
}


void PourExposeReglette (REGLETTE reglette, XExposeEvent *evmt) {

  /********** ?????????? **********/

}


void PourButtonPress (XButtonEvent *evmt) {
  if (evmt->window == reglette->fenetre) {
    PourButtonPressReglette(reglette, evmt);
  }
}


void PourMotionNotify (XPointerMovedEvent *evmt) {
  if (evmt->window == reglette->fenetre) {
    PourMotionNotifyReglette(reglette, evmt);
  }
}


void PourButtonRelease (XButtonEvent *evmt) {
  if (evmt->window == reglette->fenetre) {
    PourButtonReleaseReglette(reglette, evmt);
  }
}


void PourConfigureNotify (XConfigureEvent *evmt) {
  if (evmt->window == reglette->fenetre) {
    PourConfigureNotifyReglette(reglette, evmt);
  }
}


void PourExpose (XExposeEvent *evmt) {
  if (evmt->window == reglette->fenetre) {
    PourExposeReglette(reglette, evmt);
  }
}
