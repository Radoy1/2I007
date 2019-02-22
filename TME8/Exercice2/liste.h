#ifndef LISTE_H
#define LISTE_H

#include <qcolor.h> 


class Liste
{
  public :
    int     dx, dy, fx, fy;
    uint    epaisseur;
    QColor *couleur;
    Liste  *suite;

    Liste ();
    Liste (int dx, int dy, int fx, int fy, uint e, QColor *c);

    void   ajouterFinListe (int dx, int dy, int fx, int fy, uint e, QColor *c);
    Liste *laSuite (void);

    Liste *dernier;
};

#endif
