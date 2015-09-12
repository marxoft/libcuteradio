TEMPLATE = app
TARGET = resources-del
INSTALLS += target

INCLUDEPATH += ../../../src
LIBS += -L../../../lib -lcuteradio
SOURCES += main.cpp

unix {
    target.path = /opt/libcuteradio/bin
}
