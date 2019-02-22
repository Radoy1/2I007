#include <QWidget>
#include <QPainter>
#include <QColor>
#include <QPixmap>
#include <QMouseEvent>
#include <QPen>
#include "liste.h"

#ifndef MAWIDGET_H
#define MAWIDGET_H

typedef enum { normal, debut, elastique, fin } Etat;

class MaWidget : public QWidget
{
public :
  MaWidget (QWidget *parent=0);

  int       dx, dy, ix, iy, fx, fy;
  uint      epaisseur;
  Liste    *liste;
  QPainter *peintre;
  QColor   *couleur;
  Etat      etat;

  void mousePressEvent   (QMouseEvent *e);
  void mouseReleaseEvent (QMouseEvent *e);
  void mouseMoveEvent    (QMouseEvent *e);
  void paintEvent        (QPaintEvent *e);
};

#endif
