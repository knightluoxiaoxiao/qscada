/****************************************************************************
** Meta object code from reading C++ file 'iodriver.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/libs/iodriver/iodriver.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'iodriver.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_IODriver_t {
    QByteArrayData data[7];
    char stringdata0[45];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_IODriver_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_IODriver_t qt_meta_stringdata_IODriver = {
    {
QT_MOC_LITERAL(0, 0, 8), // "IODriver"
QT_MOC_LITERAL(1, 9, 8), // "response"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 3), // "buf"
QT_MOC_LITERAL(4, 23, 7), // "timeout"
QT_MOC_LITERAL(5, 31, 5), // "write"
QT_MOC_LITERAL(6, 37, 7) // "request"

    },
    "IODriver\0response\0\0buf\0timeout\0write\0"
    "request"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_IODriver[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,
       4,    0,   32,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   33,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QByteArray,    3,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QByteArray,    6,

       0        // eod
};

void IODriver::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        IODriver *_t = static_cast<IODriver *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->response((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 1: _t->timeout(); break;
        case 2: _t->write((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (IODriver::*_t)(QByteArray );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&IODriver::response)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (IODriver::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&IODriver::timeout)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject IODriver::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_IODriver.data,
      qt_meta_data_IODriver,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *IODriver::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *IODriver::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_IODriver.stringdata0))
        return static_cast<void*>(const_cast< IODriver*>(this));
    return QThread::qt_metacast(_clname);
}

int IODriver::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void IODriver::response(QByteArray _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void IODriver::timeout()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
