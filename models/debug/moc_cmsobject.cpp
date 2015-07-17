/****************************************************************************
** Meta object code from reading C++ file 'cmsobject.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../sqlobjects/cmsobject.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cmsobject.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CmsObject_t {
    QByteArrayData data[10];
    char stringdata0[75];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CmsObject_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CmsObject_t qt_meta_stringdata_CmsObject = {
    {
QT_MOC_LITERAL(0, 0, 9), // "CmsObject"
QT_MOC_LITERAL(1, 10, 8), // "numberID"
QT_MOC_LITERAL(2, 19, 4), // "name"
QT_MOC_LITERAL(3, 24, 8), // "nickname"
QT_MOC_LITERAL(4, 33, 8), // "password"
QT_MOC_LITERAL(5, 42, 2), // "ID"
QT_MOC_LITERAL(6, 45, 5), // "phone"
QT_MOC_LITERAL(7, 51, 6), // "belong"
QT_MOC_LITERAL(8, 58, 11), // "user_number"
QT_MOC_LITERAL(9, 70, 4) // "role"

    },
    "CmsObject\0numberID\0name\0nickname\0"
    "password\0ID\0phone\0belong\0user_number\0"
    "role"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CmsObject[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       9,   14, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // properties: name, type, flags
       1, QMetaType::QString, 0x00095003,
       2, QMetaType::QString, 0x00095003,
       3, QMetaType::QString, 0x00095003,
       4, QMetaType::QString, 0x00095003,
       5, QMetaType::QString, 0x00095103,
       6, QMetaType::Double, 0x00095003,
       7, QMetaType::QString, 0x00095003,
       8, QMetaType::QString, 0x00095003,
       9, QMetaType::Double, 0x00095003,

       0        // eod
};

void CmsObject::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{

#ifndef QT_NO_PROPERTIES
    if (_c == QMetaObject::ReadProperty) {
        CmsObject *_t = static_cast<CmsObject *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->getnumberID(); break;
        case 1: *reinterpret_cast< QString*>(_v) = _t->getname(); break;
        case 2: *reinterpret_cast< QString*>(_v) = _t->getnickname(); break;
        case 3: *reinterpret_cast< QString*>(_v) = _t->getpassword(); break;
        case 4: *reinterpret_cast< QString*>(_v) = _t->getID(); break;
        case 5: *reinterpret_cast< double*>(_v) = _t->getphone(); break;
        case 6: *reinterpret_cast< QString*>(_v) = _t->getbelong(); break;
        case 7: *reinterpret_cast< QString*>(_v) = _t->getuser_number(); break;
        case 8: *reinterpret_cast< double*>(_v) = _t->getrole(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        CmsObject *_t = static_cast<CmsObject *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setnumberID(*reinterpret_cast< QString*>(_v)); break;
        case 1: _t->setname(*reinterpret_cast< QString*>(_v)); break;
        case 2: _t->setnickname(*reinterpret_cast< QString*>(_v)); break;
        case 3: _t->setpassword(*reinterpret_cast< QString*>(_v)); break;
        case 4: _t->setID(*reinterpret_cast< QString*>(_v)); break;
        case 5: _t->setphone(*reinterpret_cast< double*>(_v)); break;
        case 6: _t->setbelong(*reinterpret_cast< QString*>(_v)); break;
        case 7: _t->setuser_number(*reinterpret_cast< QString*>(_v)); break;
        case 8: _t->setrole(*reinterpret_cast< double*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject CmsObject::staticMetaObject = {
    { &TSqlObject::staticMetaObject, qt_meta_stringdata_CmsObject.data,
      qt_meta_data_CmsObject,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CmsObject::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CmsObject::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CmsObject.stringdata0))
        return static_cast<void*>(const_cast< CmsObject*>(this));
    if (!strcmp(_clname, "QSharedData"))
        return static_cast< QSharedData*>(const_cast< CmsObject*>(this));
    return TSqlObject::qt_metacast(_clname);
}

int CmsObject::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TSqlObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    
#ifndef QT_NO_PROPERTIES
   if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 9;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 9;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 9;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 9;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 9;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
QT_END_MOC_NAMESPACE
