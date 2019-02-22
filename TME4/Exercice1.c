/**********

  Exercice1.c

  A compiler avec	gcc -o Exercice1 Exercice1.c -lX11

**********/


#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>   
#include <X11/XKBlib.h>   


Display       *dpy;
Window         wracine, wprincipale, wmenu, wrouge, wvert, wbleu;
int            ecran;
XEvent         evmt;
unsigned long  cnoir, cblanc, crouge, cvert, cbleu;
int            bouton = 0, nb_boutons_enfonces = 0;


void PourButtonPress   (XButtonPressedEvent *evmt);
//void PourButtonRelease (XButtonReleasedEvent *evmt);
void Installer         (char *serveur);
void PourKeyPress (XKeyPressedEvent *evmt);


int main (int argc, char *argv[]) {	/* la procedue main()                */
  Installer(NULL);
  for (;;) {				/* la boucle d'evenements            */
      XNextEvent(dpy, &evmt);
      switch (evmt.type) {
      case ButtonPress :
	PourButtonPress((XButtonPressedEvent *)&evmt);
	break;
	/*case ButtonRelease :
	PourButtonRelease((XButtonReleasedEvent *)&evmt);
	break;*/
      case KeyPress :
	PourKeyPress((XKeyPressedEvent *)&evmt);
	break;
      default:;
      }
  }
}


void Installer (char *serveur) {
  XSetWindowAttributes attr;

  dpy = XOpenDisplay(serveur);
  if (dpy == NULL) {
     printf("Connection impossoble avec le serveur %s.\n", serveur);
     exit(0);
  }

  wracine = DefaultRootWindow(dpy);
  ecran   = DefaultScreen(dpy);

  cnoir = 0x000000;	cblanc = 0xFFFFFF;
  crouge = 0xFF0000;	cvert = 0x00FF00;	cbleu = 0x0000FF;

  wprincipale = XCreateSimpleWindow(dpy, wracine, 0, 0, 200, 200, 0,
				   cnoir, cblanc);
  XSelectInput(dpy, wprincipale,
	       ButtonPressMask|ButtonReleaseMask|OwnerGrabButtonMask);

  /*
  attr.override_redirect = True;
  wmenu  = XCreateSimpleWindow(dpy, wracine, 0, 0, 50, 75, 1,
			       cnoir, cblanc);
  XChangeWindowAttributes(dpy, wmenu, CWOverrideRedirect, &attr);
  */
  attr.override_redirect = True;
  wmenu = XCreateWindow(dpy, wracine, 0, 0, 50, 75, 1,
			CopyFromParent, CopyFromParent, CopyFromParent,
			CWOverrideRedirect, &attr);
  wrouge = XCreateSimpleWindow(dpy, wmenu, 0, 0, 50, 25, 0, cnoir, crouge);
  wvert  = XCreateSimpleWindow(dpy, wmenu, 0, 25, 50, 25, 0, cnoir, cvert);
  wbleu  = XCreateSimpleWindow(dpy, wmenu, 0, 50, 50, 25, 0, cnoir, cbleu);
  XSelectInput(dpy,wmenu,KeyPressMask);
  
  XStoreName(dpy, wprincipale, "Exercice1");
  XMapWindow(dpy, wprincipale);

  XMapSubwindows(dpy, wmenu);

  XSetIOErrorHandler(XCloseDisplay);
}


void PourButtonPress (XButtonPressedEvent *evmt) {
    bouton = evmt->button;
    XMoveWindow(dpy, wmenu, evmt->x_root, evmt->y_root);
    XMapRaised(dpy, wmenu);
    XSetInputFocus(dpy, wmenu, RevertToNone, CurrentTime);
}

/*
void PourButtonRelease (XButtonReleasedEvent *evmt) {
  --nb_boutons_enfonces;
  if (evmt->button == bouton) {
    XUnmapWindow(dpy, wmenu);
    if (evmt->window == wrouge) {
      XSetWindowBackground(dpy, wprincipale, crouge);
      XClearWindow(dpy, wprincipale);
    } else if (evmt->window == wvert) {
      XSetWindowBackground(dpy, wprincipale, cvert);
      XClearWindow(dpy, wprincipale);
    } else if (evmt->window == wbleu) {
      XSetWindowBackground(dpy, wprincipale, cbleu);
      XClearWindow(dpy, wprincipale);
    }
    bouton = 0;
  }
}
*/
void PourKeyPress (XKeyPressedEvent *evmt){
  char *chaine = XKeysymToString(XkbKeycodeToKeysym(dpy, evmt -> keycode, 0, 0));
  printf("%s\n",chaine);
  if(strcmp("r",chaine)==0){
    XUnmapWindow(dpy, wmenu);
    XSetWindowBackground(dpy, wprincipale, 0xFF0000);
    XClearWindow(dpy, wprincipale);
  }
  if(strcmp("b",chaine)==0){
    XUnmapWindow(dpy, wmenu);
    XSetWindowBackground(dpy, wprincipale, 0x0000FF);
    XClearWindow(dpy, wprincipale);
  }
  if(strcmp("v",chaine)==0){
    XUnmapWindow(dpy, wmenu);
    XSetWindowBackground(dpy, wprincipale, 0x00FF00);
    XClearWindow(dpy, wprincipale);
  }
}
