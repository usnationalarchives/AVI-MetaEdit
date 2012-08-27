/****************************************************************************
** Meta object code from reading C++ file 'GUI_Main_xxxx__Common.h'
**
** Created: Wed 18. Jan 22:05:46 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../Source/GUI/Qt/GUI_Main_xxxx__Common.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GUI_Main_xxxx__Common.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GUI_Main_xxxx__Common[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      23,   22,   22,   22, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_GUI_Main_xxxx__Common[] = {
    "GUI_Main_xxxx__Common\0\0OnItemSelectionChanged()\0"
};

void GUI_Main_xxxx__Common::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        GUI_Main_xxxx__Common *_t = static_cast<GUI_Main_xxxx__Common *>(_o);
        switch (_id) {
        case 0: _t->OnItemSelectionChanged(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData GUI_Main_xxxx__Common::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject GUI_Main_xxxx__Common::staticMetaObject = {
    { &QTableWidget::staticMetaObject, qt_meta_stringdata_GUI_Main_xxxx__Common,
      qt_meta_data_GUI_Main_xxxx__Common, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GUI_Main_xxxx__Common::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GUI_Main_xxxx__Common::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GUI_Main_xxxx__Common::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GUI_Main_xxxx__Common))
        return static_cast<void*>(const_cast< GUI_Main_xxxx__Common*>(this));
    return QTableWidget::qt_metacast(_clname);
}

int GUI_Main_xxxx__Common::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTableWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
static const uint qt_meta_data_OriginationTimeDelegate[] = {

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

static const char qt_meta_stringdata_OriginationTimeDelegate[] = {
    "OriginationTimeDelegate\0"
};

void OriginationTimeDelegate::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData OriginationTimeDelegate::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject OriginationTimeDelegate::staticMetaObject = {
    { &QItemDelegate::staticMetaObject, qt_meta_stringdata_OriginationTimeDelegate,
      qt_meta_data_OriginationTimeDelegate, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &OriginationTimeDelegate::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *OriginationTimeDelegate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *OriginationTimeDelegate::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_OriginationTimeDelegate))
        return static_cast<void*>(const_cast< OriginationTimeDelegate*>(this));
    return QItemDelegate::qt_metacast(_clname);
}

int OriginationTimeDelegate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QItemDelegate::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_TimeReferenceDelegate[] = {

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

static const char qt_meta_stringdata_TimeReferenceDelegate[] = {
    "TimeReferenceDelegate\0"
};

void TimeReferenceDelegate::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData TimeReferenceDelegate::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject TimeReferenceDelegate::staticMetaObject = {
    { &QItemDelegate::staticMetaObject, qt_meta_stringdata_TimeReferenceDelegate,
      qt_meta_data_TimeReferenceDelegate, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TimeReferenceDelegate::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TimeReferenceDelegate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TimeReferenceDelegate::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TimeReferenceDelegate))
        return static_cast<void*>(const_cast< TimeReferenceDelegate*>(this));
    return QItemDelegate::qt_metacast(_clname);
}

int TimeReferenceDelegate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QItemDelegate::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
