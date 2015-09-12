TEMPLATE = lib

DEFINES += CUTERADIO_DEBUG
#DEFINES += CUTERADIO_STATIC_LIBRARY

QT += network
QT -= gui

TARGET = cuteradio
DESTDIR = ../lib

HEADERS += \
    json.h \
    cuteradio_global.h \
    countriesmodel.h \
    genresmodel.h \
    languagesmodel.h \
    model.h \
    model_p.h \
    request.h \
    request_p.h \
    resourcesmodel.h \
    resourcesmodel_p.h \
    resourcesrequest.h \
    searchesmodel.h \
    stationsmodel.h \
    urls.h

SOURCES += \
    json.cpp \
    countriesmodel.cpp \
    genresmodel.cpp \
    languagesmodel.cpp \
    model.cpp \
    request.cpp \
    resourcesmodel.cpp \
    resourcesrequest.cpp \
    searchesmodel.cpp \
    stationsmodel.cpp
    
headers.files += \
    cuteradio_global.h \
    countriesmodel.h \
    genresmodel.h \
    languagesmodel.h \
    model.h \
    request.h \
    resourcesmodel.h \
    resourcesrequest.h \
    searchesmodel.h \
    stationsmodel.h \
    urls.h
    
symbian {
    TARGET.CAPABILITY += NetworkServices ReadUserData WriteUserData
    TARGET.EPOCALLOWDLLDATA = 1
    TARGET.EPOCHEAPSIZE = 0x20000 0x8000000
    TARGET.EPOCSTACKSIZE = 0x14000
}

contains(DEFINES,CUTERADIO_STATIC_LIBRARY) {
    CONFIG += staticlib
    headers.path = ../include/cuteradio
    QMAKE_POST_LINK = mkdir -p $$headers.path && cp $$headers.files $$headers.path
} else {
    CONFIG += create_prl
    INSTALLS += target headers

    !isEmpty(INSTALL_SRC_PREFIX) {
        target.path = $$INSTALL_SRC_PREFIX/lib
        headers.path = $$INSTALL_SRC_PREFIX/include/cuteradio
    } else {
        target.path = /usr/lib
        headers.path = /usr/include/cuteradio
    }
}
