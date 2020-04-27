/****************************************************************************
** Meta object code from reading C++ file 'MainWindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/MainWindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MainWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[21];
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
QT_MOC_LITERAL(1, 11, 14), // "openFileAction"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 11), // "closeAction"
QT_MOC_LITERAL(4, 39, 10), // "translateX"
QT_MOC_LITERAL(5, 50, 5), // "value"
QT_MOC_LITERAL(6, 56, 10), // "translateY"
QT_MOC_LITERAL(7, 67, 10), // "translateZ"
QT_MOC_LITERAL(8, 78, 7), // "rotateX"
QT_MOC_LITERAL(9, 86, 7), // "rotateY"
QT_MOC_LITERAL(10, 94, 7), // "rotateZ"
QT_MOC_LITERAL(11, 102, 4), // "zoom"
QT_MOC_LITERAL(12, 107, 6), // "render"
QT_MOC_LITERAL(13, 114, 11), // "resetSlider"
QT_MOC_LITERAL(14, 126, 18), // "setNewGammaForMIDA"
QT_MOC_LITERAL(15, 145, 33), // "setAmountOfLayersAlphaComposi..."
QT_MOC_LITERAL(16, 179, 7), // "ambient"
QT_MOC_LITERAL(17, 187, 7), // "diffuse"
QT_MOC_LITERAL(18, 195, 8), // "specular"
QT_MOC_LITERAL(19, 204, 16), // "gradientModeCalc"
QT_MOC_LITERAL(20, 221, 18) // "gradientModeTarget"

    },
    "MainWindow\0openFileAction\0\0closeAction\0"
    "translateX\0value\0translateY\0translateZ\0"
    "rotateX\0rotateY\0rotateZ\0zoom\0render\0"
    "resetSlider\0setNewGammaForMIDA\0"
    "setAmountOfLayersAlphaCompositing\0"
    "ambient\0diffuse\0specular\0gradientModeCalc\0"
    "gradientModeTarget"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  104,    2, 0x09 /* Protected */,
       3,    0,  105,    2, 0x09 /* Protected */,
       4,    1,  106,    2, 0x09 /* Protected */,
       6,    1,  109,    2, 0x09 /* Protected */,
       7,    1,  112,    2, 0x09 /* Protected */,
       8,    1,  115,    2, 0x09 /* Protected */,
       9,    1,  118,    2, 0x09 /* Protected */,
      10,    1,  121,    2, 0x09 /* Protected */,
      11,    1,  124,    2, 0x09 /* Protected */,
      12,    1,  127,    2, 0x09 /* Protected */,
      13,    0,  130,    2, 0x09 /* Protected */,
      14,    1,  131,    2, 0x09 /* Protected */,
      15,    1,  134,    2, 0x09 /* Protected */,
      16,    1,  137,    2, 0x09 /* Protected */,
      17,    1,  140,    2, 0x09 /* Protected */,
      18,    1,  143,    2, 0x09 /* Protected */,
      19,    1,  146,    2, 0x09 /* Protected */,
      20,    1,  149,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QString,    5,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->openFileAction(); break;
        case 1: _t->closeAction(); break;
        case 2: _t->translateX((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->translateY((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->translateZ((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->rotateX((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->rotateY((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->rotateZ((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->zoom((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->render((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: _t->resetSlider(); break;
        case 11: _t->setNewGammaForMIDA((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->setAmountOfLayersAlphaCompositing((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->ambient((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->diffuse((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->specular((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: _t->gradientModeCalc((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 17: _t->gradientModeTarget((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
