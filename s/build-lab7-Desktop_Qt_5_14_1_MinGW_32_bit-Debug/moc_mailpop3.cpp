/****************************************************************************
** Meta object code from reading C++ file 'mailpop3.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../lab7/mail/mailpop3.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mailpop3.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QxtPop3_t {
    QByteArrayData data[10];
    char stringdata0[115];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QxtPop3_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QxtPop3_t qt_meta_stringdata_QxtPop3 = {
    {
QT_MOC_LITERAL(0, 0, 7), // "QxtPop3"
QT_MOC_LITERAL(1, 8, 9), // "connected"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 16), // "connectionFailed"
QT_MOC_LITERAL(4, 36, 3), // "msg"
QT_MOC_LITERAL(5, 40, 9), // "encrypted"
QT_MOC_LITERAL(6, 50, 16), // "encryptionFailed"
QT_MOC_LITERAL(7, 67, 13), // "authenticated"
QT_MOC_LITERAL(8, 81, 20), // "authenticationFailed"
QT_MOC_LITERAL(9, 102, 12) // "disconnected"

    },
    "QxtPop3\0connected\0\0connectionFailed\0"
    "msg\0encrypted\0encryptionFailed\0"
    "authenticated\0authenticationFailed\0"
    "disconnected"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QxtPop3[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x06 /* Public */,
       3,    1,   50,    2, 0x06 /* Public */,
       5,    0,   53,    2, 0x06 /* Public */,
       6,    1,   54,    2, 0x06 /* Public */,
       7,    0,   57,    2, 0x06 /* Public */,
       8,    1,   58,    2, 0x06 /* Public */,
       9,    0,   61,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,    4,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,    4,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,    4,
    QMetaType::Void,

       0        // eod
};

void QxtPop3::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QxtPop3 *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->connected(); break;
        case 1: _t->connectionFailed((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 2: _t->encrypted(); break;
        case 3: _t->encryptionFailed((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 4: _t->authenticated(); break;
        case 5: _t->authenticationFailed((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 6: _t->disconnected(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (QxtPop3::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QxtPop3::connected)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (QxtPop3::*)(const QByteArray & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QxtPop3::connectionFailed)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (QxtPop3::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QxtPop3::encrypted)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (QxtPop3::*)(const QByteArray & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QxtPop3::encryptionFailed)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (QxtPop3::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QxtPop3::authenticated)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (QxtPop3::*)(const QByteArray & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QxtPop3::authenticationFailed)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (QxtPop3::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QxtPop3::disconnected)) {
                *result = 6;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject QxtPop3::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_QxtPop3.data,
    qt_meta_data_QxtPop3,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *QxtPop3::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QxtPop3::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QxtPop3.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int QxtPop3::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void QxtPop3::connected()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void QxtPop3::connectionFailed(const QByteArray & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QxtPop3::encrypted()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void QxtPop3::encryptionFailed(const QByteArray & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void QxtPop3::authenticated()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void QxtPop3::authenticationFailed(const QByteArray & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void QxtPop3::disconnected()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
