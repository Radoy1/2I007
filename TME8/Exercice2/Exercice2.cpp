#include <Qt>
#include <qapplication.h>
#include "mamainwindow.h"


int
main(int argc, char **argv)
{
  QApplication appli(argc, argv);

  MaMainWindow *principale = new MaMainWindow(NULL);
  principale->setGeometry(0, 0, 400, 400);

  principale->setWindowTitle("Exercice 2");
  principale->show();

  return appli.exec();
}
