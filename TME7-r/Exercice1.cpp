#include <Qt>
#include <QApplication>
#include <QWidget>
#include <QHBoxLayout>
#include "monbouton.h"

int main(int argc, char **argv){
  
  QApplication appli(argc, argv);

  QWidget     *w         = new QWidget(NULL);
  QHBoxLayout *placement = new QHBoxLayout(w);
  MonBouton   *b1        = new MonBouton(QString("Bouton 1"), w);
  MonBouton   *b2        = new MonBouton(QString("Bouton 2"), w);

  placement -> addWidget(b1);
  placement -> addWidget(b2);

  b2 -> setVisible(false);

  QObject::connect(b1, SIGNAL(clicked()), b1, SLOT(hide()));
  QObject::connect(b1, SIGNAL(clicked()), b2, SLOT(show()));
  QObject::connect(b2, SIGNAL(clicked()), b2, SLOT(hide()));
  QObject::connect(b2, SIGNAL(clicked()), b1, SLOT(show()));

  QObject::connect(b1, SIGNAL(clicked()), b1, SLOT(slotCompteur()));
  QObject::connect(b1, SIGNAL(signalFin()), &appli, SLOT(quit()));

  w -> setWindowTitle("Exo1");
  w -> show();

  return appli.exec();
}
