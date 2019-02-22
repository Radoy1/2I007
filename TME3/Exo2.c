/* Exo2.c */

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
Bool           dedans         = True;

/* Les prototypes de fonctions */
void Installer	         (void);
void PourConfigureNotify (XConfigureEvent *evmt);
void PourExpose          (XExposeEvent *evmt);
void largeur_hauteur     (XFontStruct *font_attributs,
		          char *chaine, int *largeur, int *hauteur);
void PourButtonPress     (XButtonEvent *evmt);
void PourButtonRelease   (XButtonEvent *evmt);

int main (int argc, char *argv[]) { /* la procedue main()                */
  Installer();
  for (;;) {			    /* la boucle d'evenements            */
    XNextEvent(dpy, &evmt);
    switch (evmt.type) {
      case ButtonPress:
      PourButtonPress((XButtonEvent *)(&evmt));
      break;
    case ButtonRelease:
      PourButtonRelease((XButtonEvent *)(&evmt));
      break;
      case ConfigureNotify :
	PourConfigureNotify((XConfigureEvent *)(&evmt));
	break;
      case Expose :
	PourExpose((XExposeEvent *)(&evmt));
	break;
      default :;
    }
  }
}


void Installer (void) {
  XSetWindowAttributes *pierre = (XSetWindowAttributes *)malloc(sizeof
						       (XSetWindowAttributes));
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

   menu      = XCreateSimpleWindow(dpy, racine, 0, 0, 200, 100, 1,
                 noir, blanc);

   pierre->override_redirect = True;
   XChangeWindowAttributes(dpy,menu,CWOverrideRedirect,pierre);
  
   XSelectInput(dpy, principale, StructureNotifyMask|ButtonPressMask
		|ButtonReleaseMask|OwnerGrabButtonMask);
   
   XSelectInput(dpy, menu, ExposureMask|ButtonPressMask|ButtonReleaseMask);

   XSelectInput(dpy, fille[0], ExposureMask);
   XSelectInput(dpy, fille[1], ExposureMask);
   XStoreName(dpy, principale, "Exercice 1");
   XMapWindow(dpy, principale);
   XMapSubwindows(dpy, principale);

}


void PourExpose (XExposeEvent *evmt) {
  Window        racine;
  int           x, y;
  unsigned int  largeur, hauteur, largeur_bordure, profondeur;
  char         *chaine;
  int           largeur_chaine, hauteur_chaine;

  if(evmt -> window == menu){
    XGetGeometry(dpy, menu,
	       &racine, &x, &y, &largeur, &hauteur,
	       &largeur_bordure, &profondeur);
   
    largeur_hauteur(font_attributs, "Grouper" , &largeur_chaine, &hauteur_chaine);
    XDrawString(dpy, menu, gc,
	      (largeur - largeur_chaine)/2, (hauteur + hauteur_chaine)/4,
	      "Grouper", strlen("Grouper"));

     XDrawLine(dpy, menu, DefaultGC(dpy,ecran), x, hauteur/2, largeur, hauteur/2);
     
    largeur_hauteur(font_attributs, "Degrouper" , &largeur_chaine, &hauteur_chaine);
    XDrawString(dpy, menu, gc,
	      (largeur - largeur_chaine)/2, 3*(hauteur + hauteur_chaine)/4,
	      "Degrouper", strlen("Degrouper"));
  }
  else{
  XGetGeometry(dpy, evmt->window,
	       &racine, &x, &y, &largeur, &hauteur,
	       &largeur_bordure, &profondeur);
  XClearWindow(dpy, evmt->window);

  chaine = texte_fille[evmt->window == fille[0] ? 0 : 1];
  largeur_hauteur(font_attributs, chaine, &largeur_chaine, &hauteur_chaine);
  XDrawString(dpy, evmt->window, gc,
	      (largeur - largeur_chaine)/2, (hauteur + hauteur_chaine)/2,
	      chaine, strlen(chaine));
  }
}


void largeur_hauteur (XFontStruct *font_attributs,
		      char *chaine, int *largeur, int *hauteur) {

  /* On recupere la largeur de la chaine avec ce font (de ce gc) */
  *largeur = XTextWidth(font_attributs, chaine, strlen(chaine));

  /* Et la hauteur (se dit ascent (haut) et descent (bas)) des caracteres */
  *hauteur = font_attributs->ascent;
}

void PourButtonPress (XButtonPressedEvent *evmt){
  if(evmt -> window == principale){
    XMoveWindow(dpy, menu, evmt->x_root, evmt->y_root);
    XMapRaised(dpy, menu);
  }
}

void PourButtonRelease  (XButtonReleasedEvent *evmt){
  Window        racine;
  int           x, y;
  unsigned int  largeur, hauteur, largeur_bordure, profondeur;
  int           largeur_chaine, hauteur_chaine;
  

  if(evmt -> window == menu ){
     XGetGeometry(dpy, evmt -> window,
	       &racine, &x, &y, &largeur, &hauteur,
	       &largeur_bordure, &profondeur);
     if(evmt -> y >= hauteur/2){
       XReparentWindow(dpy, fille[0],racine, 0, 0);
       XReparentWindow(dpy, fille[1],racine, 0, 0);
       XResizeWindow(dpy, fille[0], largeur/2, hauteur/2);
       XResizeWindow(dpy, fille[1], largeur/2, hauteur - hauteur/2);
       dedans = False;
     }
     else{
       XReparentWindow(dpy, fille[0], principale, 0, 0);
       XReparentWindow(dpy, fille[0], principale, 0, 0);
       dedans = True;
     }
  }
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
