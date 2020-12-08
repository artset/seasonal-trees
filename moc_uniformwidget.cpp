/****************************************************************************
** Meta object code from reading C++ file 'uniformwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "uniforms/uniformwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'uniformwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_UniformWidget_t {
    QByteArrayData data[13];
    char stringdata0[142];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_UniformWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_UniformWidget_t qt_meta_stringdata_UniformWidget = {
    {
QT_MOC_LITERAL(0, 0, 13), // "UniformWidget"
QT_MOC_LITERAL(1, 14, 7), // "deleted"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 14), // "UniformWidget*"
QT_MOC_LITERAL(4, 38, 7), // "changed"
QT_MOC_LITERAL(5, 46, 22), // "const UniformVariable*"
QT_MOC_LITERAL(6, 69, 7), // "uniform"
QT_MOC_LITERAL(7, 77, 10), // "valChanged"
QT_MOC_LITERAL(8, 88, 4), // "text"
QT_MOC_LITERAL(9, 93, 9), // "updateVal"
QT_MOC_LITERAL(10, 103, 10), // "valClicked"
QT_MOC_LITERAL(11, 114, 13), // "deleteClicked"
QT_MOC_LITERAL(12, 128, 13) // "deleteUniform"

    },
    "UniformWidget\0deleted\0\0UniformWidget*\0"
    "changed\0const UniformVariable*\0uniform\0"
    "valChanged\0text\0updateVal\0valClicked\0"
    "deleteClicked\0deleteUniform"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UniformWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,
       4,    1,   52,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    1,   55,    2, 0x08 /* Private */,
       9,    0,   58,    2, 0x08 /* Private */,
      10,    0,   59,    2, 0x08 /* Private */,
      11,    0,   60,    2, 0x08 /* Private */,
      12,    0,   61,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    1,
    QMetaType::Void, 0x80000000 | 5,    6,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void UniformWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<UniformWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->deleted((*reinterpret_cast< UniformWidget*(*)>(_a[1]))); break;
        case 1: _t->changed((*reinterpret_cast< const UniformVariable*(*)>(_a[1]))); break;
        case 2: _t->valChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->updateVal(); break;
        case 4: _t->valClicked(); break;
        case 5: _t->deleteClicked(); break;
        case 6: _t->deleteUniform(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< UniformWidget* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (UniformWidget::*)(UniformWidget * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UniformWidget::deleted)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (UniformWidget::*)(const UniformVariable * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UniformWidget::changed)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject UniformWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_UniformWidget.data,
    qt_meta_data_UniformWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *UniformWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UniformWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_UniformWidget.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int UniformWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void UniformWidget::deleted(UniformWidget * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void UniformWidget::changed(const UniformVariable * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
