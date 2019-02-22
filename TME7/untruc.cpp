#include "untruc.h"

Untruc::Untruc (const QString texte, QWidget *parent) :
  QPushButton(texte, parent)
{
}

void Untruc::slotTrucAlert ()
{
  emit trucalert(true);
}

void Untruc::slotDisable (bool disable)
{
  this->setDisabled(disable);
}

void Untruc::slotEnable (bool enable)
{
  this->setEnabled(enable);
}
