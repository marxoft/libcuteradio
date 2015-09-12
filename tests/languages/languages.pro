TEMPLATE = app
TARGET = languages
INSTALLS += target

QT += widgets

INCLUDEPATH += ../../src
LIBS += -L../../lib -lcuteradio
SOURCES += main.cpp

unix {
    target.path = /opt/libcuteradio/bin
}
