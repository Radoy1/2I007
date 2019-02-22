#ifndef UNTRUC_H
#define UNTRUC_H

#include <QPushButton>

class Untruc : public QPushButton
{
  Q_OBJECT

 public :
    Untruc (const QString texte, QWidget *parent);

  public slots :
    void slotEnable(bool enable);
    void slotDisable(bool disable);
    void slotTrucAlert();
    
  signals :
    void trucalert (bool tg);
};

#endif
