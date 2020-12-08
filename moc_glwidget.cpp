/****************************************************************************
** Meta object code from reading C++ file 'glwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "glwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'glwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GLWidget_t {
    QByteArrayData data[39];
    char stringdata0[452];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GLWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GLWidget_t qt_meta_stringdata_GLWidget = {
    {
QT_MOC_LITERAL(0, 0, 8), // "GLWidget"
QT_MOC_LITERAL(1, 9, 10), // "addUniform"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 21), // "UniformVariable::Type"
QT_MOC_LITERAL(4, 43, 4), // "type"
QT_MOC_LITERAL(5, 48, 4), // "name"
QT_MOC_LITERAL(6, 53, 8), // "editable"
QT_MOC_LITERAL(7, 62, 4), // "size"
QT_MOC_LITERAL(8, 67, 16), // "UniformVariable*"
QT_MOC_LITERAL(9, 84, 7), // "uniform"
QT_MOC_LITERAL(10, 92, 13), // "changeUniform"
QT_MOC_LITERAL(11, 106, 22), // "const UniformVariable*"
QT_MOC_LITERAL(12, 129, 6), // "newVal"
QT_MOC_LITERAL(13, 136, 16), // "changeRenderMode"
QT_MOC_LITERAL(14, 153, 10), // "RenderType"
QT_MOC_LITERAL(15, 164, 4), // "mode"
QT_MOC_LITERAL(16, 169, 14), // "changeAnimMode"
QT_MOC_LITERAL(17, 184, 8), // "AnimType"
QT_MOC_LITERAL(18, 193, 19), // "toggleDrawWireframe"
QT_MOC_LITERAL(19, 213, 4), // "draw"
QT_MOC_LITERAL(20, 218, 16), // "setWireframeMode"
QT_MOC_LITERAL(21, 235, 13), // "WireframeType"
QT_MOC_LITERAL(22, 249, 10), // "loadShader"
QT_MOC_LITERAL(23, 260, 4), // "vert"
QT_MOC_LITERAL(24, 265, 4), // "frag"
QT_MOC_LITERAL(25, 270, 8), // "QString*"
QT_MOC_LITERAL(26, 279, 6), // "errors"
QT_MOC_LITERAL(27, 286, 14), // "uniformDeleted"
QT_MOC_LITERAL(28, 301, 12), // "uniformAdded"
QT_MOC_LITERAL(29, 314, 11), // "viewChanged"
QT_MOC_LITERAL(30, 326, 9), // "glm::mat4"
QT_MOC_LITERAL(31, 336, 9), // "modelview"
QT_MOC_LITERAL(32, 346, 17), // "projectionChanged"
QT_MOC_LITERAL(33, 364, 10), // "projection"
QT_MOC_LITERAL(34, 375, 26), // "modelviewProjectionChanged"
QT_MOC_LITERAL(35, 402, 19), // "modelviewProjection"
QT_MOC_LITERAL(36, 422, 12), // "modelChanged"
QT_MOC_LITERAL(37, 435, 9), // "setPaused"
QT_MOC_LITERAL(38, 445, 6) // "paused"

    },
    "GLWidget\0addUniform\0\0UniformVariable::Type\0"
    "type\0name\0editable\0size\0UniformVariable*\0"
    "uniform\0changeUniform\0const UniformVariable*\0"
    "newVal\0changeRenderMode\0RenderType\0"
    "mode\0changeAnimMode\0AnimType\0"
    "toggleDrawWireframe\0draw\0setWireframeMode\0"
    "WireframeType\0loadShader\0vert\0frag\0"
    "QString*\0errors\0uniformDeleted\0"
    "uniformAdded\0viewChanged\0glm::mat4\0"
    "modelview\0projectionChanged\0projection\0"
    "modelviewProjectionChanged\0"
    "modelviewProjection\0modelChanged\0"
    "setPaused\0paused"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GLWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      20,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    4,  114,    2, 0x06 /* Public */,
       1,    3,  123,    2, 0x26 /* Public | MethodCloned */,
       1,    2,  130,    2, 0x26 /* Public | MethodCloned */,
       1,    2,  135,    2, 0x06 /* Public */,
       1,    1,  140,    2, 0x26 /* Public | MethodCloned */,
      10,    2,  143,    2, 0x06 /* Public */,
      10,    2,  148,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      13,    1,  153,    2, 0x0a /* Public */,
      16,    1,  156,    2, 0x0a /* Public */,
      18,    1,  159,    2, 0x0a /* Public */,
      20,    1,  162,    2, 0x0a /* Public */,
      22,    3,  165,    2, 0x0a /* Public */,
      22,    2,  172,    2, 0x2a /* Public | MethodCloned */,
      27,    1,  177,    2, 0x0a /* Public */,
      28,    1,  180,    2, 0x0a /* Public */,
      29,    1,  183,    2, 0x0a /* Public */,
      32,    1,  186,    2, 0x0a /* Public */,
      34,    1,  189,    2, 0x0a /* Public */,
      36,    1,  192,    2, 0x0a /* Public */,
      37,    1,  195,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::QString, QMetaType::Bool, QMetaType::Int,    4,    5,    6,    7,
    QMetaType::Void, 0x80000000 | 3, QMetaType::QString, QMetaType::Bool,    4,    5,    6,
    QMetaType::Void, 0x80000000 | 3, QMetaType::QString,    4,    5,
    QMetaType::Void, 0x80000000 | 8, QMetaType::Bool,    9,    6,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, 0x80000000 | 11, QMetaType::QString,    9,   12,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    5,   12,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 14,   15,
    QMetaType::Void, 0x80000000 | 17,   15,
    QMetaType::Void, QMetaType::Bool,   19,
    QMetaType::Void, 0x80000000 | 21,   15,
    QMetaType::Bool, QMetaType::QString, QMetaType::QString, 0x80000000 | 25,   23,   24,   26,
    QMetaType::Bool, QMetaType::QString, QMetaType::QString,   23,   24,
    QMetaType::Void, 0x80000000 | 11,    9,
    QMetaType::Void, 0x80000000 | 11,    9,
    QMetaType::Void, 0x80000000 | 30,   31,
    QMetaType::Void, 0x80000000 | 30,   33,
    QMetaType::Void, 0x80000000 | 30,   35,
    QMetaType::Void, 0x80000000 | 30,   31,
    QMetaType::Void, QMetaType::Bool,   38,

       0        // eod
};

void GLWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GLWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->addUniform((*reinterpret_cast< UniformVariable::Type(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 1: _t->addUniform((*reinterpret_cast< UniformVariable::Type(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 2: _t->addUniform((*reinterpret_cast< UniformVariable::Type(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 3: _t->addUniform((*reinterpret_cast< UniformVariable*(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 4: _t->addUniform((*reinterpret_cast< UniformVariable*(*)>(_a[1]))); break;
        case 5: _t->changeUniform((*reinterpret_cast< const UniformVariable*(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 6: _t->changeUniform((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 7: _t->changeRenderMode((*reinterpret_cast< RenderType(*)>(_a[1]))); break;
        case 8: _t->changeAnimMode((*reinterpret_cast< AnimType(*)>(_a[1]))); break;
        case 9: _t->toggleDrawWireframe((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->setWireframeMode((*reinterpret_cast< WireframeType(*)>(_a[1]))); break;
        case 11: { bool _r = _t->loadShader((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString*(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 12: { bool _r = _t->loadShader((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 13: _t->uniformDeleted((*reinterpret_cast< const UniformVariable*(*)>(_a[1]))); break;
        case 14: _t->uniformAdded((*reinterpret_cast< const UniformVariable*(*)>(_a[1]))); break;
        case 15: _t->viewChanged((*reinterpret_cast< const glm::mat4(*)>(_a[1]))); break;
        case 16: _t->projectionChanged((*reinterpret_cast< const glm::mat4(*)>(_a[1]))); break;
        case 17: _t->modelviewProjectionChanged((*reinterpret_cast< const glm::mat4(*)>(_a[1]))); break;
        case 18: _t->modelChanged((*reinterpret_cast< const glm::mat4(*)>(_a[1]))); break;
        case 19: _t->setPaused((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (GLWidget::*)(UniformVariable::Type , const QString & , bool , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GLWidget::addUniform)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (GLWidget::*)(UniformVariable * , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GLWidget::addUniform)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (GLWidget::*)(const UniformVariable * , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GLWidget::changeUniform)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (GLWidget::*)(const QString & , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GLWidget::changeUniform)) {
                *result = 6;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject GLWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QGLWidget::staticMetaObject>(),
    qt_meta_stringdata_GLWidget.data,
    qt_meta_data_GLWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *GLWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GLWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GLWidget.stringdata0))
        return static_cast<void*>(this);
    return QGLWidget::qt_metacast(_clname);
}

int GLWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 20)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 20;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 20)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 20;
    }
    return _id;
}

// SIGNAL 0
void GLWidget::addUniform(UniformVariable::Type _t1, const QString & _t2, bool _t3, int _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 3
void GLWidget::addUniform(UniformVariable * _t1, bool _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 5
void GLWidget::changeUniform(const UniformVariable * _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void GLWidget::changeUniform(const QString & _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
