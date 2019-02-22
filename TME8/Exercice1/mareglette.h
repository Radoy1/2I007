/********** mareglette.h **********/

#ifndef MAREGLETTE_H
#define MAREGLETTE_H

#include <QSlider> 


class MaReglette : public QSlider
{
  Q_OBJECT

 public :
  MaReglette (Qt::Orientation orientation, QWidget * parent = 0);

  public slots :
    void slotNormal (int);
    void slotUnite (int);
};


#endif
