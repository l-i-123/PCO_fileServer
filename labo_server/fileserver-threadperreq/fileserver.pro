QT       += core websockets
QT       += testlib
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
    hoaremonitor.cpp \
    runnabletask.cpp \
    tst_threadpool.cpp \
    readerwritercache.cpp \
    readerwriterlock.cpp

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
    hoaremonitor.h \
    runnabletask.h \
    tst_threadpool.h \
    option.h \
    readerwritercache.h \
    readerwriterlock.h

EXAMPLE_FILES += fileclient.html

