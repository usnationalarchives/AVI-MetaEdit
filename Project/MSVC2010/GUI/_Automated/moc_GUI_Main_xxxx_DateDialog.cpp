/****************************************************************************
** Meta object code from reading C++ file 'GUI_Main_xxxx_DateDialog.h'
**
** Created: Wed 18. Jan 22:05:46 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../Source/GUI/Qt/GUI_Main_xxxx_DateDialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GUI_Main_xxxx_DateDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GUI_Main_xxxx_DateDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      26,   25,   25,   25, 0x08,
      37,   25,   25,   25, 0x08,
      58,   25,   25,   25, 0x08,
      72,   25,   25,   25, 0x08,
      90,   25,   25,   25, 0x08,
     104,   25,   25,   25, 0x08,
     126,  120,   25,   25, 0x08,
     154,  148,   25,   25, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_GUI_Main_xxxx_DateDialog[] = {
    "GUI_Main_xxxx_DateDialog\0\0OnAccept()\0"
    "OnCalendar_Changed()\0OnMenu_Date()\0"
    "OnMenu_Calendar()\0OnMenu_Text()\0"
    "OnTextChanged()\0Index\0OnCurrentChanged(int)\0"
    "State\0OnTimeActivatedChanged(int)\0"
};

void GUI_Main_xxxx_DateDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        GUI_Main_xxxx_DateDialog *_t = static_cast<GUI_Main_xxxx_DateDialog *>(_o);
        switch (_id) {
        case 0: _t->OnAccept(); break;
        case 1: _t->OnCalendar_Changed(); break;
        case 2: _t->OnMenu_Date(); break;
        case 3: _t->OnMenu_Calendar(); break;
        case 4: _t->OnMenu_Text(); break;
        case 5: _t->OnTextChanged(); break;
        case 6: _t->OnCurrentChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->OnTimeActivatedChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData GUI_Main_xxxx_DateDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject GUI_Main_xxxx_DateDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_GUI_Main_xxxx_DateDialog,
      qt_meta_data_GUI_Main_xxxx_DateDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GUI_Main_xxxx_DateDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GUI_Main_xxxx_DateDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GUI_Main_xxxx_DateDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GUI_Main_xxxx_DateDialog))
        return static_cast<void*>(const_cast< GUI_Main_xxxx_DateDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int GUI_Main_xxxx_DateDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
