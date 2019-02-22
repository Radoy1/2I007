/****************************************************************************
** Meta object code from reading C++ file 'mamainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mamainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mamainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MaMainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x0a,
      27,   13,   13,   13, 0x0a,
      41,   13,   13,   13, 0x0a,
      56,   13,   13,   13, 0x0a,
      74,   13,   13,   13, 0x0a,
      96,   13,   13,   13, 0x0a,
     110,   13,   13,   13, 0x0a,
     124,   13,   13,   13, 0x0a,
     140,   13,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MaMainWindow[] = {
    "MaMainWindow\0\0slotOuvrir()\0slotNouveau()\0"
    "slotImprimer()\0slotEnregistrer()\0"
    "slotEnregistrerSous()\0slotQuitter()\0"
    "slotCouleur()\0slotEpaisseur()\0slotAide()\0"
};

void MaMainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MaMainWindow *_t = static_cast<MaMainWindow *>(_o);
        switch (_id) {
        case 0: _t->slotOuvrir(); break;
        case 1: _t->slotNouveau(); break;
        case 2: _t->slotImprimer(); break;
        case 3: _t->slotEnregistrer(); break;
        case 4: _t->slotEnregistrerSous(); break;
        case 5: _t->slotQuitter(); break;
        case 6: _t->slotCouleur(); break;
        case 7: _t->slotEpaisseur(); break;
        case 8: _t->slotAide(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData MaMainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MaMainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MaMainWindow,
      qt_meta_data_MaMainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MaMainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MaMainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MaMainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MaMainWindow))
        return static_cast<void*>(const_cast< MaMainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MaMainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
