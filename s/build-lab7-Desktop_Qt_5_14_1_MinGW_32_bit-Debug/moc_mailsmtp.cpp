/****************************************************************************
** Meta object code from reading C++ file 'mailsmtp.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../lab7/mail/mailsmtp.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mailsmtp.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QxtSmtp_t {
    QByteArrayData data[18];
    char stringdata0[202];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QxtSmtp_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QxtSmtp_t qt_meta_stringdata_QxtSmtp = {
    {
QT_MOC_LITERAL(0, 0, 7), // "QxtSmtp"
QT_MOC_LITERAL(1, 8, 9), // "connected"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 16), // "connectionFailed"
QT_MOC_LITERAL(4, 36, 3), // "msg"
QT_MOC_LITERAL(5, 40, 9), // "encrypted"
QT_MOC_LITERAL(6, 50, 16), // "encryptionFailed"
QT_MOC_LITERAL(7, 67, 13), // "authenticated"
QT_MOC_LITERAL(8, 81, 20), // "authenticationFailed"
QT_MOC_LITERAL(9, 102, 14), // "senderRejected"
QT_MOC_LITERAL(10, 117, 6), // "mailID"
QT_MOC_LITERAL(11, 124, 7), // "address"
QT_MOC_LITERAL(12, 132, 17), // "recipientRejected"
QT_MOC_LITERAL(13, 150, 10), // "mailFailed"
QT_MOC_LITERAL(14, 161, 9), // "errorCode"
QT_MOC_LITERAL(15, 171, 8), // "mailSent"
QT_MOC_LITERAL(16, 180, 8), // "finished"
QT_MOC_LITERAL(17, 189, 12) // "disconnected"

    },
    "QxtSmtp\0connected\0\0connectionFailed\0"
    "msg\0encrypted\0encryptionFailed\0"
    "authenticated\0authenticationFailed\0"
    "senderRejected\0mailID\0address\0"
    "recipientRejected\0mailFailed\0errorCode\0"
    "mailSent\0finished\0disconnected"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QxtSmtp[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      18,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  104,    2, 0x06 /* Public */,
       3,    0,  105,    2, 0x06 /* Public */,
       3,    1,  106,    2, 0x06 /* Public */,
       5,    0,  109,    2, 0x06 /* Public */,
       6,    0,  110,    2, 0x06 /* Public */,
       6,    1,  111,    2, 0x06 /* Public */,
       7,    0,  114,    2, 0x06 /* Public */,
       8,    0,  115,    2, 0x06 /* Public */,
       8,    1,  116,    2, 0x06 /* Public */,
       9,    2,  119,    2, 0x06 /* Public */,
       9,    3,  124,    2, 0x06 /* Public */,
      12,    2,  131,    2, 0x06 /* Public */,
      12,    3,  136,    2, 0x06 /* Public */,
      13,    2,  143,    2, 0x06 /* Public */,
      13,    3,  148,    2, 0x06 /* Public */,
      15,    1,  155,    2, 0x06 /* Public */,
      16,    0,  158,    2, 0x06 /* Public */,
      17,    0,  159,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,    4,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,   10,   11,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::QByteArray,   10,   11,    4,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,   10,   11,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::QByteArray,   10,   11,    4,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   10,   14,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::QByteArray,   10,   14,    4,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void QxtSmtp::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QxtSmtp *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->connected(); break;
        case 1: _t->connectionFailed(); break;
        case 2: _t->connectionFailed((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 3: _t->encrypted(); break;
        case 4: _t->encryptionFailed(); break;
        case 5: _t->encryptionFailed((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 6: _t->authenticated(); break;
        case 7: _t->authenticationFailed(); break;
        case 8: _t->authenticationFailed((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 9: _t->senderRejected((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 10: _t->senderRejected((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QByteArray(*)>(_a[3]))); break;
        case 11: _t->recipientRejected((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 12: _t->recipientRejected((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QByteArray(*)>(_a[3]))); break;
        case 13: _t->mailFailed((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 14: _t->mailFailed((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< const QByteArray(*)>(_a[3]))); break;
        case 15: _t->mailSent((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: _t->finished(); break;
        case 17: _t->disconnected(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (QxtSmtp::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QxtSmtp::connected)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (QxtSmtp::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QxtSmtp::connectionFailed)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (QxtSmtp::*)(const QByteArray & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QxtSmtp::connectionFailed)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (QxtSmtp::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QxtSmtp::encrypted)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (QxtSmtp::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QxtSmtp::encryptionFailed)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (QxtSmtp::*)(const QByteArray & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QxtSmtp::encryptionFailed)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (QxtSmtp::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QxtSmtp::authenticated)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (QxtSmtp::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QxtSmtp::authenticationFailed)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (QxtSmtp::*)(const QByteArray & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QxtSmtp::authenticationFailed)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (QxtSmtp::*)(int , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QxtSmtp::senderRejected)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (QxtSmtp::*)(int , const QString & , const QByteArray & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QxtSmtp::senderRejected)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (QxtSmtp::*)(int , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QxtSmtp::recipientRejected)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (QxtSmtp::*)(int , const QString & , const QByteArray & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QxtSmtp::recipientRejected)) {
                *result = 12;
                return;
            }
        }
        {
            using _t = void (QxtSmtp::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QxtSmtp::mailFailed)) {
                *result = 13;
                return;
            }
        }
        {
            using _t = void (QxtSmtp::*)(int , int , const QByteArray & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QxtSmtp::mailFailed)) {
                *result = 14;
                return;
            }
        }
        {
            using _t = void (QxtSmtp::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QxtSmtp::mailSent)) {
                *result = 15;
                return;
            }
        }
        {
            using _t = void (QxtSmtp::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QxtSmtp::finished)) {
                *result = 16;
                return;
            }
        }
        {
            using _t = void (QxtSmtp::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QxtSmtp::disconnected)) {
                *result = 17;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject QxtSmtp::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_QxtSmtp.data,
    qt_meta_data_QxtSmtp,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *QxtSmtp::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QxtSmtp::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QxtSmtp.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int QxtSmtp::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 18)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 18;
    }
    return _id;
}

// SIGNAL 0
void QxtSmtp::connected()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void QxtSmtp::connectionFailed()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void QxtSmtp::connectionFailed(const QByteArray & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void QxtSmtp::encrypted()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void QxtSmtp::encryptionFailed()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void QxtSmtp::encryptionFailed(const QByteArray & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void QxtSmtp::authenticated()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void QxtSmtp::authenticationFailed()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void QxtSmtp::authenticationFailed(const QByteArray & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void QxtSmtp::senderRejected(int _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void QxtSmtp::senderRejected(int _t1, const QString & _t2, const QByteArray & _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void QxtSmtp::recipientRejected(int _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void QxtSmtp::recipientRejected(int _t1, const QString & _t2, const QByteArray & _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void QxtSmtp::mailFailed(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void QxtSmtp::mailFailed(int _t1, int _t2, const QByteArray & _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void QxtSmtp::mailSent(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}

// SIGNAL 16
void QxtSmtp::finished()
{
    QMetaObject::activate(this, &staticMetaObject, 16, nullptr);
}

// SIGNAL 17
void QxtSmtp::disconnected()
{
    QMetaObject::activate(this, &staticMetaObject, 17, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
