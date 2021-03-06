QT       += core websockets
QT       -= gui

TARGET = fileserver
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += \
    main.cpp \
    fileserver.cpp \
    filereader.cpp \
    requesthandler.cpp \
    responsedispatcherthread.cpp \
    requestdispatcherthread.cpp \
    sendrequestthread.cpp \
    threadpool.cpp \
    runnabletask.cpp

HEADERS += \
    fileserver.h \
    filereader.h \
    response.h \
    abstractbuffer.h \
    request.h \
    requesthandler.h \
    responsedispatcherthread.h \
    mesabuffer.h \
    requestdispatcherthread.h \
    sendrequestthread.h \
    runnable.h \
    threadpool.h \
    runnabletask.h

EXAMPLE_FILES += fileclient.html

