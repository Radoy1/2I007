
/* Exo2.c */

#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <stdlib.h>
#include <stdio.h>


Display *dpy;
GC       gc;


/* ?????????? (1) ?????????? */
void PourButtonPress(XButtonEvent *evmt,int wi,int h,Window w);

int main (int argc, char *argv[]) {	/* la procedue main()                */
  Window          racine, principale, w;
  XEvent          evmt;
  XConfigureEvent evmt_envoi;
  int             width, height;

  /* ?????????? (2) ?????????? */
  printf("Donnez l'ID de la fenetre, puis largeur, puis hauteur.\n");
  printf("Par exemple : 0x8c00002 200 400\n");

  scanf("%x %d %d", &w, &width, &height);
  printf("0x%x\n", w);

  dpy = XOpenDisplay(NULL);
  racine = DefaultRootWindow(dpy);
  principale = XCreateSimpleWindow(dpy,
		  racine,
                  0, 0, 200, 200,
                  0,
                  0x0, 0xFFFFFF);

  /* ?????????? (3) ?????????? */
  XSelectInput(dpy,principale,ButtonPressMask); 
  XStoreName(dpy, principale, "Exercice 2");
  XMapWindow(dpy, principale);

  /* ?????????? (4) ?????????? */
  for(;;){
     XNextEvent(dpy,&evmt);
     switch(evmt.type){
        case ButtonPress: PourButtonPress((XButtonEvent *)&evmt,width,height,w);break;
     default:break;
     }
   }
  
}


/* ?????????? (4) ?????????? */
void PourButtonPress(XButtonEvent *evmt,int wi,int h,Window w){

  XResizeWindow(dpy,w,wi,h);

}
/*
      printf("Donnez l'ID de la fenetre, puis largeur, puis hauteur.\n");
      printf("Par exemple : 0x8c00002 200 400\n");

      scanf("%x %d %d", &w, &width, &height);
      printf("0x%x\n", w);
*/
