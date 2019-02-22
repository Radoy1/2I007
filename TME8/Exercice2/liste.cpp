#include "liste.h"


Liste::Liste () {}


Liste::Liste (int dx, int dy, int fx, int fy, uint e, QColor *c)
{
  dernier = NULL;
  this->dx = dx;
  this->dy = dy;
  this->fx = fx;
  this->fy = fy;
  epaisseur = e;
  couleur = c;
  suite = NULL;
  dernier = this;

}


void
Liste::ajouterFinListe (int dx, int dy, int fx, int fy, uint e, QColor *c)
{
  Liste *aux = new Liste();

  aux->dx = dx;
  aux->dy = dy;
  aux->fx = fx;
  aux->fy = fy;
  aux->epaisseur = e;
  aux->couleur   = c;
  aux->suite     = NULL;
  dernier->suite = aux;
  dernier        = aux;
}


Liste *
Liste::laSuite (void)
{
  return (suite);
}
