/****************************************************************************
** Meta object code from reading C++ file 'mainForm.h'
**
** Created: Sun 13. Oct 12:57:41 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainForm.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainForm.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_mainForm[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x0a,
      21,    9,    9,    9, 0x0a,
      35,    9,    9,    9, 0x0a,
      49,    9,    9,    9, 0x0a,
      71,    9,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_mainForm[] = {
    "mainForm\0\0openFile()\0displayHelp()\0"
    "encodeVideo()\0updateGUIPreview(int)\0"
    "updateGUIUserDefinedVideo(int)\0"
};

void mainForm::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        mainForm *_t = static_cast<mainForm *>(_o);
        switch (_id) {
        case 0: _t->openFile(); break;
        case 1: _t->displayHelp(); break;
        case 2: _t->encodeVideo(); break;
        case 3: _t->updateGUIPreview((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->updateGUIUserDefinedVideo((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData mainForm::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject mainForm::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_mainForm,
      qt_meta_data_mainForm, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &mainForm::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *mainForm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *mainForm::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_mainForm))
        return static_cast<void*>(const_cast< mainForm*>(this));
    return QDialog::qt_metacast(_clname);
}

int mainForm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
