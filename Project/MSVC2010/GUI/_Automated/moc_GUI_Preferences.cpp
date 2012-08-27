/****************************************************************************
** Meta object code from reading C++ file 'GUI_Preferences.h'
**
** Created: Wed 18. Jan 22:05:46 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../Source/GUI/Qt/GUI_Preferences.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GUI_Preferences.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GUI_Preferences[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x08,
      26,   16,   16,   16, 0x08,
      35,   16,   16,   16, 0x08,
      48,   16,   16,   16, 0x08,
      82,   16,   16,   16, 0x08,
     102,   94,   16,   16, 0x08,
     154,   94,   16,   16, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_GUI_Preferences[] = {
    "GUI_Preferences\0\0OnLoad()\0OnSave()\0"
    "OnRejected()\0OnDialogClicked(QAbstractButton*)\0"
    "OnClicked()\0Checked\0"
    "OnExtra_BackupDirectory_Specific_RadioToggled(bool)\0"
    "OnExtra_LogFile_Activated_RadioToggled(bool)\0"
};

void GUI_Preferences::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        GUI_Preferences *_t = static_cast<GUI_Preferences *>(_o);
        switch (_id) {
        case 0: _t->OnLoad(); break;
        case 1: _t->OnSave(); break;
        case 2: _t->OnRejected(); break;
        case 3: _t->OnDialogClicked((*reinterpret_cast< QAbstractButton*(*)>(_a[1]))); break;
        case 4: _t->OnClicked(); break;
        case 5: _t->OnExtra_BackupDirectory_Specific_RadioToggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->OnExtra_LogFile_Activated_RadioToggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData GUI_Preferences::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject GUI_Preferences::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_GUI_Preferences,
      qt_meta_data_GUI_Preferences, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GUI_Preferences::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GUI_Preferences::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GUI_Preferences::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GUI_Preferences))
        return static_cast<void*>(const_cast< GUI_Preferences*>(this));
    return QDialog::qt_metacast(_clname);
}

int GUI_Preferences::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
