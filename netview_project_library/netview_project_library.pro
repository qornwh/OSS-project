QT -= gui

TEMPLATE = lib
DEFINES += NETVIEW_PROJECT_LIBRARY_LIBRARY

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    pcap_config.cpp \
    pcap_ether_header.cpp \
    pcap_ip.cpp \
    pcap_ip_header.cpp \
    pcap_mac.cpp \
    pcap_work.cpp

HEADERS += \
    netview_project_library_global.h \
    pcap_config.h \
    pcap_ether_header.h \
    pcap_ip.h \
    pcap_ip_header.h \
    pcap_mac.h \
    pcap_work.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

DEFINES += WPCAP
DEFINES += HAVE_REMOTE

win32:LIBS += -L$$PWD/../WpdPack/Lib/ -lwpcap -lws2_32
win32:LIBS += -lws2_32

INCLUDEPATH += $$PWD/../WpdPack/Include
DEPENDPATH += $$PWD/../WpdPack/Include
