/**********

  Exercice2.c

  A compiler avec	gcc -o Exercice2 Exercice2.c -lX11

**********/


#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <string.h>


Display       *dpy;
Window         wracine, wprincipale, lautre;
int            ecran;
XEvent         evmt;
GC             gc;
unsigned long  cnoir, cblanc;
Atom           XA_RDV, XA_NUMERO;


void Installer         (char *serveur);


int main (int argc, char *argv[]) {	/* la procedue main()                */
  XClientMessageEvent cm;
  char                chaine[200];

  Installer(NULL);
  for (;;) {				/* la boucle d'evenements            */
      XNextEvent(dpy, &evmt);
      switch (evmt.type) {
      case SelectionClear :
	lautre = XGetSelectionOwner(dpy, XA_RDV);

	cm.type      = ClientMessage;
	cm.format    = 32;
	cm.data.l[0] = wprincipale;
	XSendEvent(dpy, lautre, False, 0L, (XEvent *)&cm);
	sprintf(chaine, "%ld", wprincipale);
	XChangeProperty(dpy, lautre, XA_NUMERO, XA_STRING, 8,
			PropModeReplace, chaine, strlen(chaine));
	lautre = None;
	break;
      case ClientMessage :
	sprintf(chaine, "%ld", evmt.xclient.data.l[0]);
	XDrawString(dpy, wprincipale, gc, 100, 100, chaine, strlen(chaine));
	printf("%s\n",chaine);
	if (lautre != None) {
	  cm.type      = ClientMessage;
	  cm.format    = 32;
	  cm.data.l[0] = wprincipale;
	  XSendEvent(dpy, lautre, False, 0L, (XEvent *)&cm);
	  sprintf(chaine, "%ld", wprincipale);
	  XChangeProperty(dpy, lautre, XA_NUMERO, XA_STRING, 8,
			  PropModeReplace, chaine, strlen(chaine));
	  lautre = None;
	}
	break;
      case PropertyNotify :
	if (evmt.xproperty.atom == XA_NUMERO &&
	    evmt.xproperty.state == PropertyNewValue) {
	  Atom           type_effectif_retour;
	  int            format_effectif_retour;
	  unsigned long  nb_lus_retour, nb_octets_restants_retour;
	  unsigned char *donnees_retournees;
	  char           chaine[100];

	  XGetWindowProperty(dpy, wprincipale, XA_NUMERO, 0, 100,
			     True, XA_STRING,
			     &type_effectif_retour, &format_effectif_retour,
			     &nb_lus_retour, &nb_octets_restants_retour,
			     &donnees_retournees);
	  strncpy(chaine, donnees_retournees, nb_lus_retour);
	  XDrawString(dpy, wprincipale, gc, 100, 150, chaine, nb_lus_retour);
	  printf("%s\n",chaine);
	}
	break;
      default:;
      }
  }
}


void Installer (char *serveur) {
  XSetWindowAttributes attr;

  dpy = XOpenDisplay(serveur);
  if (dpy == NULL) {
     printf("Connection impossible avec le serveur %s.\n", serveur);
     exit(0);
  }

  wracine = DefaultRootWindow(dpy);
  ecran   = DefaultScreen(dpy);
  gc      = DefaultGC(dpy, ecran);

  cnoir = 0x000000;	cblanc = 0xFFFFFF;

  wprincipale = XCreateSimpleWindow(dpy, wracine, 0, 0, 200, 200, 0,
				   cnoir, cblanc);
  XSelectInput(dpy, wprincipale, PropertyChangeMask);

  printf("wprincipale = %d\n", wprincipale);

  XMapWindow(dpy, wprincipale);


  XA_NUMERO = XInternAtom(dpy, "NUMERO", False);
  XA_RDV    = XInternAtom(dpy, "RDV", False);

  lautre = XGetSelectionOwner(dpy, XA_RDV);
  XSetSelectionOwner(dpy, XA_RDV, wprincipale, CurrentTime);

  XSetIOErrorHandler(XCloseDisplay);
}
