/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[32];
    char stringdata0[548];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 14), // "removeUniforms"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 4), // "init"
QT_MOC_LITERAL(4, 32, 23), // "on_sphereButton_clicked"
QT_MOC_LITERAL(5, 56, 21), // "on_treeButton_clicked"
QT_MOC_LITERAL(6, 78, 30), // "on_defaultShaderButton_clicked"
QT_MOC_LITERAL(7, 109, 24), // "on_shader2Button_clicked"
QT_MOC_LITERAL(8, 134, 28), // "on_summerRadioButton_clicked"
QT_MOC_LITERAL(9, 163, 26), // "on_fallRadioButton_clicked"
QT_MOC_LITERAL(10, 190, 28), // "on_winterRadioButton_clicked"
QT_MOC_LITERAL(11, 219, 28), // "on_springRadioButton_clicked"
QT_MOC_LITERAL(12, 248, 32), // "on_treeOptionsComboBox_activated"
QT_MOC_LITERAL(13, 281, 4), // "arg1"
QT_MOC_LITERAL(14, 286, 42), // "on_treeOptionsComboBox_curren..."
QT_MOC_LITERAL(15, 329, 5), // "index"
QT_MOC_LITERAL(16, 335, 26), // "on_bumpMapCheckbox_clicked"
QT_MOC_LITERAL(17, 362, 20), // "handleUniformDeleted"
QT_MOC_LITERAL(18, 383, 14), // "UniformWidget*"
QT_MOC_LITERAL(19, 398, 7), // "deleted"
QT_MOC_LITERAL(20, 406, 13), // "changeUniform"
QT_MOC_LITERAL(21, 420, 22), // "const UniformVariable*"
QT_MOC_LITERAL(22, 443, 7), // "uniform"
QT_MOC_LITERAL(23, 451, 6), // "newVal"
QT_MOC_LITERAL(24, 458, 4), // "name"
QT_MOC_LITERAL(25, 463, 10), // "addUniform"
QT_MOC_LITERAL(26, 474, 21), // "UniformVariable::Type"
QT_MOC_LITERAL(27, 496, 4), // "type"
QT_MOC_LITERAL(28, 501, 8), // "editable"
QT_MOC_LITERAL(29, 510, 4), // "size"
QT_MOC_LITERAL(30, 515, 16), // "UniformVariable*"
QT_MOC_LITERAL(31, 532, 15) // "settingsChanged"

    },
    "MainWindow\0removeUniforms\0\0init\0"
    "on_sphereButton_clicked\0on_treeButton_clicked\0"
    "on_defaultShaderButton_clicked\0"
    "on_shader2Button_clicked\0"
    "on_summerRadioButton_clicked\0"
    "on_fallRadioButton_clicked\0"
    "on_winterRadioButton_clicked\0"
    "on_springRadioButton_clicked\0"
    "on_treeOptionsComboBox_activated\0arg1\0"
    "on_treeOptionsComboBox_currentIndexChanged\0"
    "index\0on_bumpMapCheckbox_clicked\0"
    "handleUniformDeleted\0UniformWidget*\0"
    "deleted\0changeUniform\0const UniformVariable*\0"
    "uniform\0newVal\0name\0addUniform\0"
    "UniformVariable::Type\0type\0editable\0"
    "size\0UniformVariable*\0settingsChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      22,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  124,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,  125,    2, 0x08 /* Private */,
       4,    0,  126,    2, 0x08 /* Private */,
       5,    0,  127,    2, 0x08 /* Private */,
       6,    0,  128,    2, 0x08 /* Private */,
       7,    0,  129,    2, 0x08 /* Private */,
       8,    0,  130,    2, 0x08 /* Private */,
       9,    0,  131,    2, 0x08 /* Private */,
      10,    0,  132,    2, 0x08 /* Private */,
      11,    0,  133,    2, 0x08 /* Private */,
      12,    1,  134,    2, 0x08 /* Private */,
      14,    1,  137,    2, 0x08 /* Private */,
      16,    0,  140,    2, 0x08 /* Private */,
      17,    1,  141,    2, 0x0a /* Public */,
      20,    2,  144,    2, 0x0a /* Public */,
      20,    2,  149,    2, 0x0a /* Public */,
      25,    4,  154,    2, 0x0a /* Public */,
      25,    3,  163,    2, 0x2a /* Public | MethodCloned */,
      25,    2,  170,    2, 0x2a /* Public | MethodCloned */,
      25,    2,  175,    2, 0x0a /* Public */,
      25,    1,  180,    2, 0x2a /* Public | MethodCloned */,
      31,    0,  183,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   13,
    QMetaType::Void, QMetaType::Int,   15,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 18,   19,
    QMetaType::Void, 0x80000000 | 21, QMetaType::QString,   22,   23,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   24,   23,
    QMetaType::Void, 0x80000000 | 26, QMetaType::QString, QMetaType::Bool, QMetaType::Int,   27,   24,   28,   29,
    QMetaType::Void, 0x80000000 | 26, QMetaType::QString, QMetaType::Bool,   27,   24,   28,
    QMetaType::Void, 0x80000000 | 26, QMetaType::QString,   27,   24,
    QMetaType::Void, 0x80000000 | 30, QMetaType::Bool,   22,   28,
    QMetaType::Void, 0x80000000 | 30,   22,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->removeUniforms(); break;
        case 1: _t->init(); break;
        case 2: _t->on_sphereButton_clicked(); break;
        case 3: _t->on_treeButton_clicked(); break;
        case 4: _t->on_defaultShaderButton_clicked(); break;
        case 5: _t->on_shader2Button_clicked(); break;
        case 6: _t->on_summerRadioButton_clicked(); break;
        case 7: _t->on_fallRadioButton_clicked(); break;
        case 8: _t->on_winterRadioButton_clicked(); break;
        case 9: _t->on_springRadioButton_clicked(); break;
        case 10: _t->on_treeOptionsComboBox_activated((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 11: _t->on_treeOptionsComboBox_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->on_bumpMapCheckbox_clicked(); break;
        case 13: _t->handleUniformDeleted((*reinterpret_cast< UniformWidget*(*)>(_a[1]))); break;
        case 14: _t->changeUniform((*reinterpret_cast< const UniformVariable*(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 15: _t->changeUniform((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 16: _t->addUniform((*reinterpret_cast< UniformVariable::Type(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 17: _t->addUniform((*reinterpret_cast< UniformVariable::Type(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 18: _t->addUniform((*reinterpret_cast< UniformVariable::Type(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 19: _t->addUniform((*reinterpret_cast< UniformVariable*(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 20: _t->addUniform((*reinterpret_cast< UniformVariable*(*)>(_a[1]))); break;
        case 21: _t->settingsChanged(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::removeUniforms)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
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
        if (_id < 22)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 22;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 22)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 22;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::removeUniforms()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
