QT -= gui
QT += core network

CONFIG += c++11
QMAKE_CXXFLAGS += -std=c++11
TARGET = fa6_pi
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    Server/nanoNetInterfaceConfig.cpp \
    Server/onega_ip.cpp \
    Server/raspiNetInterfaceConfig.cpp \
    tcp.cpp \
    Server/helloworldcontroller.cpp \
    Server/listdatacontroller.cpp \
    Server/logincontroller.cpp \
    Server/requestmapper.cpp

HEADERS += \
    tcp.h \
    Server/helloworldcontroller.h \
    Server/listdatacontroller.h \
    Server/logincontroller.h \
    Server/requestmapper.h \
    RTP/RTP.h \
    RTP/Proto.h \
    RTP/Macros.h \
    RTP/Types.h \
    RTP/Network.h \
    variables.h


include("QtWebApp/httpserver/httpserver.pri")
OTHER_FILES += etc/webapp1.ini
    
target.path = /home/pi
INSTALLS += target

DISTFILES +=
