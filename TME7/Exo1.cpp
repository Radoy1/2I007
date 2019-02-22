#include <Qt>
#include <QApplication>
#include <QWidget>
#include <QHBoxLayout>
#include "monbouton.h"
#include "untruc.h"

int
main(int argc, char **argv)
{
  QApplication appli(argc, argv);

  QWidget     *w         = new QWidget(NULL);
  QHBoxLayout *placement = new QHBoxLayout(w);
  Untruc   *b1        = new Untruc(QString("Bouton 1"), w);
  Untruc   *b2        = new Untruc(QString("Bouton 2"), w);

  placement->addWidget(b1);
  placement->addWidget(b2);
  QObject::connect(b1,SIGNAL(clicked()), b1, SLOT(slotTrucAlert()));
  QObject::connect(b2,SIGNAL(clicked()), b2, SLOT(slotTrucAlert())); 

  QObject::connect(b1, SIGNAL(trucalert(bool)), b1, SLOT(slotDisable(bool)));
  QObject::connect(b1, SIGNAL(trucalert(bool)), b2, SLOT(slotEnable(bool)));
  QObject::connect(b2, SIGNAL(trucalert(bool)), b2, SLOT(slotDisable(bool)));
  QObject::connect(b2, SIGNAL(trucalert(bool)), b1, SLOT(slotEnable(bool)));

  QObject::connect(b1, SIGNAL(clicked()), b1, SLOT(slotCompteur()));
  QObject::connect(b1, SIGNAL(signalFin()), &appli, SLOT(quit()));


  w->setWindowTitle("Exo1_2");
  w->show();

  return appli.exec();
}
