/********** exemple2_2.cpp **********/

#include <QApplication>
#include <QWidget>
#include <QSlider>
#include <QLabel>
#include "mareglette.h"


int
main(int argc, char *argv[])
{
  QApplication appli(argc, argv);

  QWidget    *principale = new QWidget();

  principale->setWindowTitle("Exercice 1");
  principale->setGeometry(0, 0, 520, 200);

  QLabel *affichage = new QLabel(principale);
  affichage->setGeometry(10, 10, 500, 50);
  affichage->setAlignment(Qt::AlignHCenter);
  affichage->setNum(0);

  MaReglette *normal = new MaReglette(Qt::Horizontal, principale);
  normal->setRange(0, 100);			/* echelle de 0 à 100     */
  normal->setSliderPosition(0);		/* le depart a 0          */
  normal->setGeometry(10, 70, 500, 50);
  normal->setTickPosition(QSlider::TicksBelow);/* traits affiches en bas */
  normal->setTickInterval(1);			/* unite entre deux traits*/
  
  MaReglette *unite = new MaReglette(Qt::Horizontal, principale);
  unite->setRange(0, 9);
  unite->setSliderPosition(0);
  unite->setGeometry(10, 130, 500, 50);
  unite->setTickPosition(QSlider::TicksBelow);
  unite->setTickInterval(1);

  QObject::connect(
             normal, SIGNAL(valueChanged(int)),
	     affichage, SLOT(setNum(int)));

  QObject::connect(
             normal, SIGNAL(valueChanged(int)),
	     unite, SLOT(slotUnite(int)));

  QObject::connect(
             unite, SIGNAL(valueChanged(int)),
	     normal, SLOT(slotNormal(int)));

 principale->show();

  return appli.exec();
}
