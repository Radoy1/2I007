/* Exo2.c */

#include <X11/Xlib.h>
#include <stdlib.h>
#include <stdio.h>


Display	      *dpy;			/* le serveur			     */
int	       ecran;			/* son ecran par defaut		     */
GC             gc;
Window	       racine, principale, fille;
unsigned long  noire, rouge, blanche;	/* les differents pixels de couleur  */
XEvent	       evmt;
int            prin,fil;


/* ?????????? (1) ?????????? */


/* Les prototypes de fonctions */
void Installer	         (void);
void PourExpose(XExposeEvent *evmt);
void PourConfigureNotify(XConfigureEvent *evmt);


int main (int argc, char *argv[]) {	/* la procedue main()                */
  Installer();

  for(;;){
    XNextEvent(dpy,&evmt);
    switch(evmt.type){
       case Expose: PourExpose((XExposeEvent *)&evmt);break;
       case ConfigureNotify: PourConfigureNotify((XConfigureEvent *)&evmt);printf("event\n");break;
    default : break;
      }
    }

}


void Installer (void) {
  dpy    = XOpenDisplay(NULL);
  racine = DefaultRootWindow(dpy);
  ecran  = DefaultScreen(dpy);
  gc     = DefaultGC(dpy, ecran);

  rouge   = 0xFF0000;	/* ne fonctionne que si le serveur est en TrueColor  */
  noire   = 0x0;	/*    ou DirectColor. Sinon, il faut s'adresser a la */
  blanche = 0xFFFFFF;	/*    table de couleur Colormap du serveur           */

  XSetForeground(dpy,gc,rouge);
  
  principale = XCreateSimpleWindow(dpy,
		  racine,
                  0, 0, 200, 200,
                  0,
                  noire, blanche);
  fille      = XCreateSimpleWindow(dpy,
                  principale,
                  50, 50, 100, 100,
                  1,
                  noire, blanche);

  XSelectInput(dpy,principale,StructureNotifyMask|ExposureMask);
  XSelectInput(dpy,fille,ExposureMask|StructureNotifyMask);
  XStoreName(dpy, principale, "Exercice 1");
  XMapWindow(dpy, principale);
  XMapSubwindows(dpy, principale);
}

void PourExpose(XExposeEvent *evmt){
    
  Window root;
  int i,pas,x,y,height,width,border_w,depth;
  
  XGetGeometry(dpy,evmt->window,&root,&x,&y,&width,&height,&border_w,&depth);
  XClearWindow(dpy,evmt->window);
  if(evmt->window == principale){
    pas=height/10;
    for(i=0;i<10;i++)
      XDrawLine(dpy,principale,gc,0,i*pas,width,i*pas);
   }else{
    pas=width/10;
    for(i=0;i<10;i++)
      XDrawLine(dpy,fille,gc,i*pas,0,i*pas,height);
   }
}

void PourConfigureNotify(XConfigureEvent *evmt){
 
  if(evmt->window == principale && (!prin || !fil)){
    XMoveWindow(dpy,fille,evmt->width/4,evmt->height/4);
    XResizeWindow(dpy,fille,evmt->width/2,evmt->height/2);
    printf("event\n");
  }else if(!prin || !fil){
    XResizeWindow(dpy,principale,evmt->width*2,evmt->height*2);
  }
  

}
