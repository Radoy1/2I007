#include "monbouton.h"

MonBouton::MonBouton (const QString texte, QWidget *parent) :
  QPushButton(texte, parent)
{
}


void MonBouton::slotCompteur ()
{
  static int compteur = 1;

  if (compteur == 10)
    emit signalFin();
  else compteur++;
}
