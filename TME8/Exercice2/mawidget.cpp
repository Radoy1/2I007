#include "mawidget.h"


MaWidget::MaWidget (QWidget *parent) : QWidget(parent)
{
  peintre = new QPainter();
}


void
MaWidget::mousePressEvent (QMouseEvent *e)
{
  dx   = ix = fx = e->x();
  dy   = iy = fy = e->y();
  etat = debut;
  repaint();
}


void
MaWidget::mouseReleaseEvent (QMouseEvent *e)
{
  ix = fx = e-> x();
  iy = fy = e-> y();
  etat = fin;
  if(liste==NULL){
    liste = new Liste(dx,dy,fx,fy,epaisseur,couleur);
  }else{
    liste->ajouterFinListe(dx,dy,fx,fy,epaisseur,couleur);
  }
  repaint();
}


void
MaWidget::mouseMoveEvent (QMouseEvent *e)
{
  ix   = fx = e->x();
  iy   = fy = e->y();
  etat = elastique;
  repaint();
}


void
MaWidget::paintEvent (QPaintEvent *e)
{
  QPen ancien_p;
  static QPen *p = new QPen();
  const static QPen p_gris(QColor("grey"));

  switch(etat){
  case debut:
    peintre -> begin(this);
    ancien_p = peintre -> pen();
    peintre -> setPen(p_gris);
    peintre -> setCompositionMode(QPainter::RasterOp_SourceXorDestination);
    peintre -> drawLine (dx,dy,fx,fy);
    peintre -> setPen(ancien_p);
    peintre -> end();
    break;
  case elastique:
    peintre -> begin(this);
    ancien_p = peintre -> pen();
    peintre -> setPen(p_gris);
    peintre -> setCompositionMode(QPainter::RasterOp_SourceXorDestination);
    peintre -> drawLine (dx,dy,fx,fy);
    peintre -> drawLine (dx,dy,fx,fy);
    peintre -> setPen(ancien_p);
    peintre -> end();
    break;
  case fin:
    peintre -> begin(this);
    peintre -> setCompositionMode(QPainter::RasterOp_SourceAndNotDestination);
    peintre -> drawLine (dx,dy,fx,fy);
    peintre -> end();
    break;
  default:
    while (liste!=NULL){
      peintre -> begin(this);
      peintre -> setCompositionMode(QPainter::RasterOp_SourceAndNotDestination);
      peintre -> drawLine (liste -> dx, liste -> dy, liste -> fx, liste -> fy);
      peintre -> end();
    }
    break;
  }
}
