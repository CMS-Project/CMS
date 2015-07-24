TARGET = model
TEMPLATE = lib
CONFIG += shared c++11
QT += sql
QT -= gui
DEFINES += TF_DLL
DESTDIR = ../lib
INCLUDEPATH += ../helpers sqlobjects mongoobjects
DEPENDPATH  += ../helpers sqlobjects mongoobjects
LIBS += -L../lib -lhelper

include(../appbase.pri)

HEADERS += sqlobjects/cmsobject.h
HEADERS += cms.h
SOURCES += cms.cpp
HEADERS += sqlobjects/adminsobject.h
HEADERS += admins.h
SOURCES += admins.cpp
HEADERS += sqlobjects/operatorsobject.h
HEADERS += operators.h
SOURCES += operators.cpp
HEADERS += sqlobjects/connectionobject.h
HEADERS += connection.h
SOURCES += connection.cpp
HEADERS += sqlobjects/traderecordobject.h
HEADERS += traderecord.h
SOURCES += traderecord.cpp
HEADERS += sqlobjects/assetsunitobject.h
HEADERS += assetsunit.h
SOURCES += assetsunit.cpp
HEADERS += sqlobjects/assetsunitmmanagerobject.h
HEADERS += assetsunitmmanager.h
SOURCES += assetsunitmmanager.cpp
HEADERS += sqlobjects/marketingunitobject.h
HEADERS += marketingunit.h
SOURCES += marketingunit.cpp
