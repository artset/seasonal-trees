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
    QByteArrayData data[41];
    char stringdata0[792];
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
QT_MOC_LITERAL(5, 56, 21), // "on_cubeButton_clicked"
QT_MOC_LITERAL(6, 78, 29), // "on_cylinderTreeButton_clicked"
QT_MOC_LITERAL(7, 108, 25), // "on_coneTreeButton_clicked"
QT_MOC_LITERAL(8, 134, 30), // "on_defaultShaderButton_clicked"
QT_MOC_LITERAL(9, 165, 25), // "on_animMoveButton_clicked"
QT_MOC_LITERAL(10, 191, 25), // "on_animNoneButton_clicked"
QT_MOC_LITERAL(11, 217, 26), // "on_animScaleButton_clicked"
QT_MOC_LITERAL(12, 244, 30), // "on_animScaleMoveButton_clicked"
QT_MOC_LITERAL(13, 275, 28), // "on_animRotate1Button_clicked"
QT_MOC_LITERAL(14, 304, 28), // "on_animRotate2Button_clicked"
QT_MOC_LITERAL(15, 333, 21), // "on_tipsButton_clicked"
QT_MOC_LITERAL(16, 355, 24), // "on_shader1Button_clicked"
QT_MOC_LITERAL(17, 380, 24), // "on_shader2Button_clicked"
QT_MOC_LITERAL(18, 405, 28), // "on_summerRadioButton_clicked"
QT_MOC_LITERAL(19, 434, 26), // "on_fallRadioButton_clicked"
QT_MOC_LITERAL(20, 461, 28), // "on_winterRadioButton_clicked"
QT_MOC_LITERAL(21, 490, 28), // "on_springRadioButton_clicked"
QT_MOC_LITERAL(22, 519, 32), // "on_treeOptionsComboBox_activated"
QT_MOC_LITERAL(23, 552, 4), // "arg1"
QT_MOC_LITERAL(24, 557, 42), // "on_treeOptionsComboBox_curren..."
QT_MOC_LITERAL(25, 600, 5), // "index"
QT_MOC_LITERAL(26, 606, 20), // "handleUniformDeleted"
QT_MOC_LITERAL(27, 627, 14), // "UniformWidget*"
QT_MOC_LITERAL(28, 642, 7), // "deleted"
QT_MOC_LITERAL(29, 650, 13), // "changeUniform"
QT_MOC_LITERAL(30, 664, 22), // "const UniformVariable*"
QT_MOC_LITERAL(31, 687, 7), // "uniform"
QT_MOC_LITERAL(32, 695, 6), // "newVal"
QT_MOC_LITERAL(33, 702, 4), // "name"
QT_MOC_LITERAL(34, 707, 10), // "addUniform"
QT_MOC_LITERAL(35, 718, 21), // "UniformVariable::Type"
QT_MOC_LITERAL(36, 740, 4), // "type"
QT_MOC_LITERAL(37, 745, 8), // "editable"
QT_MOC_LITERAL(38, 754, 4), // "size"
QT_MOC_LITERAL(39, 759, 16), // "UniformVariable*"
QT_MOC_LITERAL(40, 776, 15) // "settingsChanged"

    },
    "MainWindow\0removeUniforms\0\0init\0"
    "on_sphereButton_clicked\0on_cubeButton_clicked\0"
    "on_cylinderTreeButton_clicked\0"
    "on_coneTreeButton_clicked\0"
    "on_defaultShaderButton_clicked\0"
    "on_animMoveButton_clicked\0"
    "on_animNoneButton_clicked\0"
    "on_animScaleButton_clicked\0"
    "on_animScaleMoveButton_clicked\0"
    "on_animRotate1Button_clicked\0"
    "on_animRotate2Button_clicked\0"
    "on_tipsButton_clicked\0on_shader1Button_clicked\0"
    "on_shader2Button_clicked\0"
    "on_summerRadioButton_clicked\0"
    "on_fallRadioButton_clicked\0"
    "on_winterRadioButton_clicked\0"
    "on_springRadioButton_clicked\0"
    "on_treeOptionsComboBox_activated\0arg1\0"
    "on_treeOptionsComboBox_currentIndexChanged\0"
    "index\0handleUniformDeleted\0UniformWidget*\0"
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
      31,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  169,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,  170,    2, 0x08 /* Private */,
       4,    0,  171,    2, 0x08 /* Private */,
       5,    0,  172,    2, 0x08 /* Private */,
       6,    0,  173,    2, 0x08 /* Private */,
       7,    0,  174,    2, 0x08 /* Private */,
       8,    0,  175,    2, 0x08 /* Private */,
       9,    0,  176,    2, 0x08 /* Private */,
      10,    0,  177,    2, 0x08 /* Private */,
      11,    0,  178,    2, 0x08 /* Private */,
      12,    0,  179,    2, 0x08 /* Private */,
      13,    0,  180,    2, 0x08 /* Private */,
      14,    0,  181,    2, 0x08 /* Private */,
      15,    0,  182,    2, 0x08 /* Private */,
      16,    0,  183,    2, 0x08 /* Private */,
      17,    0,  184,    2, 0x08 /* Private */,
      18,    0,  185,    2, 0x08 /* Private */,
      19,    0,  186,    2, 0x08 /* Private */,
      20,    0,  187,    2, 0x08 /* Private */,
      21,    0,  188,    2, 0x08 /* Private */,
      22,    1,  189,    2, 0x08 /* Private */,
      24,    1,  192,    2, 0x08 /* Private */,
      26,    1,  195,    2, 0x0a /* Public */,
      29,    2,  198,    2, 0x0a /* Public */,
      29,    2,  203,    2, 0x0a /* Public */,
      34,    4,  208,    2, 0x0a /* Public */,
      34,    3,  217,    2, 0x2a /* Public | MethodCloned */,
      34,    2,  224,    2, 0x2a /* Public | MethodCloned */,
      34,    2,  229,    2, 0x0a /* Public */,
      34,    1,  234,    2, 0x2a /* Public | MethodCloned */,
      40,    0,  237,    2, 0x0a /* Public */,

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
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   23,
    QMetaType::Void, QMetaType::Int,   25,
    QMetaType::Void, 0x80000000 | 27,   28,
    QMetaType::Void, 0x80000000 | 30, QMetaType::QString,   31,   32,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   33,   32,
    QMetaType::Void, 0x80000000 | 35, QMetaType::QString, QMetaType::Bool, QMetaType::Int,   36,   33,   37,   38,
    QMetaType::Void, 0x80000000 | 35, QMetaType::QString, QMetaType::Bool,   36,   33,   37,
    QMetaType::Void, 0x80000000 | 35, QMetaType::QString,   36,   33,
    QMetaType::Void, 0x80000000 | 39, QMetaType::Bool,   31,   37,
    QMetaType::Void, 0x80000000 | 39,   31,
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
        case 3: _t->on_cubeButton_clicked(); break;
        case 4: _t->on_cylinderTreeButton_clicked(); break;
        case 5: _t->on_coneTreeButton_clicked(); break;
        case 6: _t->on_defaultShaderButton_clicked(); break;
        case 7: _t->on_animMoveButton_clicked(); break;
        case 8: _t->on_animNoneButton_clicked(); break;
        case 9: _t->on_animScaleButton_clicked(); break;
        case 10: _t->on_animScaleMoveButton_clicked(); break;
        case 11: _t->on_animRotate1Button_clicked(); break;
        case 12: _t->on_animRotate2Button_clicked(); break;
        case 13: _t->on_tipsButton_clicked(); break;
        case 14: _t->on_shader1Button_clicked(); break;
        case 15: _t->on_shader2Button_clicked(); break;
        case 16: _t->on_summerRadioButton_clicked(); break;
        case 17: _t->on_fallRadioButton_clicked(); break;
        case 18: _t->on_winterRadioButton_clicked(); break;
        case 19: _t->on_springRadioButton_clicked(); break;
        case 20: _t->on_treeOptionsComboBox_activated((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 21: _t->on_treeOptionsComboBox_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 22: _t->handleUniformDeleted((*reinterpret_cast< UniformWidget*(*)>(_a[1]))); break;
        case 23: _t->changeUniform((*reinterpret_cast< const UniformVariable*(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 24: _t->changeUniform((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 25: _t->addUniform((*reinterpret_cast< UniformVariable::Type(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 26: _t->addUniform((*reinterpret_cast< UniformVariable::Type(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 27: _t->addUniform((*reinterpret_cast< UniformVariable::Type(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 28: _t->addUniform((*reinterpret_cast< UniformVariable*(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 29: _t->addUniform((*reinterpret_cast< UniformVariable*(*)>(_a[1]))); break;
        case 30: _t->settingsChanged(); break;
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
        if (_id < 31)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 31;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 31)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 31;
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
