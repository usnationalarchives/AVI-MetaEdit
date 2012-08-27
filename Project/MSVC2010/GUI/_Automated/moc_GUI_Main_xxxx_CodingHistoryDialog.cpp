/****************************************************************************
** Meta object code from reading C++ file 'GUI_Main_xxxx_CodingHistoryDialog.h'
**
** Created: Wed 18. Jan 22:05:46 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../Source/GUI/Qt/GUI_Main_xxxx_CodingHistoryDialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GUI_Main_xxxx_CodingHistoryDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GUI_Main_xxxx_CodingHistoryDialog[] = {

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
      35,   34,   34,   34, 0x08,
      46,   34,   34,   34, 0x08,
      60,   34,   34,   34, 0x08,
      74,   34,   34,   34, 0x08,
      88,   34,   34,   34, 0x08,
     154,  102,   34,   34, 0x08,
     203,  197,   34,   34, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_GUI_Main_xxxx_CodingHistoryDialog[] = {
    "GUI_Main_xxxx_CodingHistoryDialog\0\0"
    "OnAccept()\0OnMenu_Load()\0OnMenu_Save()\0"
    "OnMenu_List()\0OnMenu_Text()\0"
    "currentRow,currentColumn,previousRow,previousColumn\0"
    "OnMenu_currentCellChanged(int,int,int,int)\0"
    "Index\0OnCurrentChanged(int)\0"
};

void GUI_Main_xxxx_CodingHistoryDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        GUI_Main_xxxx_CodingHistoryDialog *_t = static_cast<GUI_Main_xxxx_CodingHistoryDialog *>(_o);
        switch (_id) {
        case 0: _t->OnAccept(); break;
        case 1: _t->OnMenu_Load(); break;
        case 2: _t->OnMenu_Save(); break;
        case 3: _t->OnMenu_List(); break;
        case 4: _t->OnMenu_Text(); break;
        case 5: _t->OnMenu_currentCellChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 6: _t->OnCurrentChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData GUI_Main_xxxx_CodingHistoryDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject GUI_Main_xxxx_CodingHistoryDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_GUI_Main_xxxx_CodingHistoryDialog,
      qt_meta_data_GUI_Main_xxxx_CodingHistoryDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GUI_Main_xxxx_CodingHistoryDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GUI_Main_xxxx_CodingHistoryDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GUI_Main_xxxx_CodingHistoryDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GUI_Main_xxxx_CodingHistoryDialog))
        return static_cast<void*>(const_cast< GUI_Main_xxxx_CodingHistoryDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int GUI_Main_xxxx_CodingHistoryDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
static const uint qt_meta_data_CodingHistoryDialog_Delegate[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_CodingHistoryDialog_Delegate[] = {
    "CodingHistoryDialog_Delegate\0"
};

void CodingHistoryDialog_Delegate::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData CodingHistoryDialog_Delegate::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CodingHistoryDialog_Delegate::staticMetaObject = {
    { &QItemDelegate::staticMetaObject, qt_meta_stringdata_CodingHistoryDialog_Delegate,
      qt_meta_data_CodingHistoryDialog_Delegate, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CodingHistoryDialog_Delegate::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CodingHistoryDialog_Delegate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CodingHistoryDialog_Delegate::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CodingHistoryDialog_Delegate))
        return static_cast<void*>(const_cast< CodingHistoryDialog_Delegate*>(this));
    return QItemDelegate::qt_metacast(_clname);
}

int CodingHistoryDialog_Delegate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QItemDelegate::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
