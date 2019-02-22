#include <Qt>
#include <qapplication.h>
#include "mamainwindow.h"


int
main(int argc, char **argv)
{
  QApplication appli(argc, argv);

  MaMainWindow *w = new MaMainWindow(NULL);
  w->setGeometry(0, 0, 400, 400);

  w->setWindowTitle("Exo2");
  w->show();

  return appli.exec();
}
