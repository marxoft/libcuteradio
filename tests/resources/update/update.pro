TEMPLATE = app
TARGET = resources-update
INSTALLS += target

INCLUDEPATH += ../../../src
LIBS += -L../../../lib -lcuteradio
SOURCES += main.cpp

unix {
    target.path = /opt/libcuteradio/bin
}
