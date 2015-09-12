TEMPLATE = app
TARGET = resources-get
INSTALLS += target

INCLUDEPATH += ../../../src
LIBS += -L../../../lib -lcuteradio
SOURCES += main.cpp

unix {
    target.path = /opt/libcuteradio/bin
}
