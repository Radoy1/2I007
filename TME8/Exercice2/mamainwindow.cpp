#include "mamainwindow.h"


MaMainWindow::MaMainWindow (QWidget *parent=0) :
  QMainWindow(parent)
{
  QAction *action;
  //statusBar();
  ppf = menuBar() -> addMenu(tr("&Fichier"));
  
  action = new QAction(tr("Nouveau"),this);
  ppf -> addAction(action);

  action = new QAction(tr("Imprimer"),this);
  ppf -> addAction(action);

  ppe = menuBar() -> addMenu(tr("&Edit"));

  action = new QAction(tr("Couleur"),this);
  ppe -> addAction(action);

  action = new QAction(tr("Epaisseur"),this);
  ppe -> addAction(action);
  
  
  planche = new MaWidget(this);
  
  setCentralWidget(planche);
  planche -> show();
}


void
MaMainWindow::slotNouveau ()
{
  
}


void
MaMainWindow::slotOuvrir ()
{
}


void
MaMainWindow::slotImprimer ()
{

}


void
MaMainWindow::slotEnregistrer ()
{
}


void
MaMainWindow::slotEnregistrerSous ()
{
}


void
MaMainWindow::slotQuitter ()
{
  
}


void
MaMainWindow::slotCouleur ()
{
  QColor c = QColorDialog::getColor();
}


void
MaMainWindow::slotEpaisseur ()
{
  bool ok;
  int e;
  e = QInputDialog::getInteger(NULL,"Epaisseur","Entier entre 1 et 10", planche -> epaisseur, 1, 10,
			       1,&ok);
}

void
MaMainWindow::slotAide()
{
}
