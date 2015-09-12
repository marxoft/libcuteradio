TEMPLATE = app
TARGET = resources-insert
INSTALLS += target

INCLUDEPATH += ../../../src
LIBS += -L../../../lib -lcuteradio
SOURCES += main.cpp

unix {
    target.path = /opt/libcuteradio/bin
}
