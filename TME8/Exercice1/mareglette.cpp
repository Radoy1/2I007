/********** mareglette.cpp **********/

#include "mareglette.h"


MaReglette::MaReglette (Qt::Orientation orientation, QWidget * parent) :
  QSlider(orientation, parent)
{
}



void
MaReglette::slotNormal (int k)
{
  setValue(value() / 10 * 10 + k);
}


void
MaReglette::slotUnite (int k)
{
  setValue(k % 10);
}
