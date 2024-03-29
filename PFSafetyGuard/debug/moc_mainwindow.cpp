/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_myThread_t {
    QByteArrayData data[10];
    char stringdata0[103];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_myThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_myThread_t qt_meta_stringdata_myThread = {
    {
QT_MOC_LITERAL(0, 0, 8), // "myThread"
QT_MOC_LITERAL(1, 9, 8), // "newValue"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 3), // "str"
QT_MOC_LITERAL(4, 23, 7), // "newInfo"
QT_MOC_LITERAL(5, 31, 14), // "newProcessName"
QT_MOC_LITERAL(6, 46, 12), // "newProcessID"
QT_MOC_LITERAL(7, 59, 18), // "newProcessPriority"
QT_MOC_LITERAL(8, 78, 17), // "newProcessModules"
QT_MOC_LITERAL(9, 96, 6) // "status"

    },
    "myThread\0newValue\0\0str\0newInfo\0"
    "newProcessName\0newProcessID\0"
    "newProcessPriority\0newProcessModules\0"
    "status"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_myThread[] = {

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
       1,    1,   49,    2, 0x06 /* Public */,
       4,    0,   52,    2, 0x06 /* Public */,
       5,    1,   53,    2, 0x06 /* Public */,
       6,    1,   56,    2, 0x06 /* Public */,
       7,    1,   59,    2, 0x06 /* Public */,
       8,    1,   62,    2, 0x06 /* Public */,
       4,    2,   65,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    3,    9,

       0        // eod
};

void myThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<myThread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->newValue((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->newInfo(); break;
        case 2: _t->newProcessName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->newProcessID((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->newProcessPriority((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->newProcessModules((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->newInfo((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (myThread::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&myThread::newValue)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (myThread::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&myThread::newInfo)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (myThread::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&myThread::newProcessName)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (myThread::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&myThread::newProcessID)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (myThread::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&myThread::newProcessPriority)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (myThread::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&myThread::newProcessModules)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (myThread::*)(QString , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&myThread::newInfo)) {
                *result = 6;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject myThread::staticMetaObject = { {
    &QThread::staticMetaObject,
    qt_meta_stringdata_myThread.data,
    qt_meta_data_myThread,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *myThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *myThread::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_myThread.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int myThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
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
void myThread::newValue(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void myThread::newInfo()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void myThread::newProcessName(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void myThread::newProcessID(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void myThread::newProcessPriority(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void myThread::newProcessModules(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void myThread::newInfo(QString _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[13];
    char stringdata0[240];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 25), // "on_openFileButton_pressed"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 21), // "on_tempButton_pressed"
QT_MOC_LITERAL(4, 60, 20), // "on_clsButton_pressed"
QT_MOC_LITERAL(5, 81, 19), // "on_ThreadA_newValue"
QT_MOC_LITERAL(6, 101, 3), // "str"
QT_MOC_LITERAL(7, 105, 18), // "on_ThreadA_newInfo"
QT_MOC_LITERAL(8, 124, 25), // "on_ThreadA_newProcessName"
QT_MOC_LITERAL(9, 150, 23), // "on_ThreadA_newProcessID"
QT_MOC_LITERAL(10, 174, 29), // "on_ThreadA_newProcessPriority"
QT_MOC_LITERAL(11, 204, 28), // "on_ThreadA_newProcessModules"
QT_MOC_LITERAL(12, 233, 6) // "status"

    },
    "MainWindow\0on_openFileButton_pressed\0"
    "\0on_tempButton_pressed\0on_clsButton_pressed\0"
    "on_ThreadA_newValue\0str\0on_ThreadA_newInfo\0"
    "on_ThreadA_newProcessName\0"
    "on_ThreadA_newProcessID\0"
    "on_ThreadA_newProcessPriority\0"
    "on_ThreadA_newProcessModules\0status"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x08 /* Private */,
       3,    0,   65,    2, 0x08 /* Private */,
       4,    0,   66,    2, 0x08 /* Private */,
       5,    1,   67,    2, 0x08 /* Private */,
       7,    0,   70,    2, 0x08 /* Private */,
       8,    1,   71,    2, 0x08 /* Private */,
       9,    1,   74,    2, 0x08 /* Private */,
      10,    1,   77,    2, 0x08 /* Private */,
      11,    1,   80,    2, 0x08 /* Private */,
       7,    2,   83,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    6,   12,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_openFileButton_pressed(); break;
        case 1: _t->on_tempButton_pressed(); break;
        case 2: _t->on_clsButton_pressed(); break;
        case 3: _t->on_ThreadA_newValue((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->on_ThreadA_newInfo(); break;
        case 5: _t->on_ThreadA_newProcessName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->on_ThreadA_newProcessID((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->on_ThreadA_newProcessPriority((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: _t->on_ThreadA_newProcessModules((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: _t->on_ThreadA_newInfo((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
