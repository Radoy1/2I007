#ifndef MAMAINWINDOW_H
#define MAMAINWINDOW_H

#include <qapplication.h>
#include <qmainwindow.h>
#include <qmenubar.h>
#include <qcolordialog.h>
#include <qinputdialog.h>
#include <qmessagebox.h>
#include <qmenu.h>
#include <qmenubar.h>
#include <qprinter.h>
#include <qdir.h>
#include <qfiledialog.h>
#include <QPrintDialog>
#include "mawidget.h"

class MaMainWindow : public QMainWindow
{
  Q_OBJECT

  public :
    MaMainWindow (QWidget *parent);

  public :
    QMenuBar    *mb;
    QMenu       *ppf, *ppe;
    MaWidget    *planche;
    QString      fichier;
    QFileDialog *file_dialog;

  public slots :
    void slotOuvrir          ();
    void slotNouveau         ();
    void slotImprimer        ();
    void slotEnregistrer     ();
    void slotEnregistrerSous ();
    void slotQuitter         ();
    void slotCouleur         ();
    void slotEpaisseur       ();
    void slotAide            ();
};


#endif
