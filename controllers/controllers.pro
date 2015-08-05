TARGET = controller
TEMPLATE = lib
CONFIG += shared c++11
QT += network sql xml
QT -= gui
DEFINES += TF_DLL
DESTDIR = ../lib
INCLUDEPATH += ../helpers ../models
DEPENDPATH  += ../helpers ../models
LIBS += -L../lib -lhelper -lmodel

include(../appbase.pri)

HEADERS += applicationcontroller.h
SOURCES += applicationcontroller.cpp
HEADERS += cmscontroller.h
SOURCES += cmscontroller.cpp
HEADERS += adminscontroller.h
SOURCES += adminscontroller.cpp
HEADERS += operatorscontroller.h
SOURCES += operatorscontroller.cpp
#HEADERS += traderecordcontroller.h
#SOURCES += traderecordcontroller.cpp
HEADERS += assetsunitcontroller.h
SOURCES += assetsunitcontroller.cpp
#HEADERS += assetsunitmmanagercontroller.h
#SOURCES += assetsunitmmanagercontroller.cpp
HEADERS += marketingunitcontroller.h
SOURCES += marketingunitcontroller.cpp
HEADERS += assetsunitmanagercontroller.h
SOURCES += assetsunitmanagercontroller.cpp
HEADERS += auoperationrecordcontroller.h
SOURCES += auoperationrecordcontroller.cpp
