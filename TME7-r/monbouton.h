#ifndef MONBOUTON_H
#define MONBOUTON_H

#include <QPushButton>

class MonBouton : public QPushButton {

  Q_OBJECT

 public :
  MonBouton (const QString texte, QWidget *parent);

  public slots:
    void slotCompteur ();

 signals:
    void signalFin();
};

#endif
