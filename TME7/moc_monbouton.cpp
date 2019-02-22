/****************************************************************************
** Meta object code from reading C++ file 'monbouton.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "monbouton.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'monbouton.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MonBouton[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
      23,   10,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MonBouton[] = {
    "MonBouton\0\0signalFin()\0slotCompteur()\0"
};

void MonBouton::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MonBouton *_t = static_cast<MonBouton *>(_o);
        switch (_id) {
        case 0: _t->signalFin(); break;
        case 1: _t->slotCompteur(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData MonBouton::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MonBouton::staticMetaObject = {
    { &QPushButton::staticMetaObject, qt_meta_stringdata_MonBouton,
      qt_meta_data_MonBouton, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MonBouton::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MonBouton::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MonBouton::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MonBouton))
        return static_cast<void*>(const_cast< MonBouton*>(this));
    return QPushButton::qt_metacast(_clname);
}

int MonBouton::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPushButton::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void MonBouton::signalFin()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
