TEMPLATE = lib
TARGET = cuteradioplugin
CONFIG += qt plugin
LIBS += -L../lib -lcuteradio

lessThan(QT_MAJOR_VERSION, 5) {
    QT += declarative
} else {
    QT += qml
}

INCLUDEPATH += ../src

HEADERS += \
    plugin.h

SOURCES += \
    plugin.cpp
    
contains(DEFINES,CUTERADIO_STATIC_LIBRARY) {
    CONFIG += link_pkgconfig
} else {
    CONFIG += link_prl
    PKGCONFIG = libcuteradio
}

qml.files = qmldir

!isEmpty(INSTALL_QML_PREFIX) {
    qml.path = $$INSTALL_QML_PREFIX/lib/qt4/imports/CuteRadio
    target.path = $$INSTALL_QML_PREFIX/lib/qt4/imports/CuteRadio
} else:lessThan(QT_MAJOR_VERSION, 5) {
    qml.path = $$[QT_INSTALL_IMPORTS]/CuteRadio
    target.path = $$[QT_INSTALL_IMPORTS]/CuteRadio
} else {
    qml.path = $$[QT_INSTALL_QML]/CuteRadio
    target.path = $$[QT_INSTALL_QML]/CuteRadio
}

INSTALLS += qml target
