QT += widgets core network sql

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Factory/dataprocessor.cpp \
    Factory/fileprocessor.cpp \
    Factory/networkprocessor.cpp \
    Factory/sqlprocessor.cpp \
    Loaders/fileloader.cpp \
    Loaders/idataloader.cpp \
    Loaders/networkloader.cpp \
    Loaders/sqlloader.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Factory/dataprocessor.h \
    Factory/fileprocessor.h \
    Factory/networkprocessor.h \
    Factory/sqlprocessor.h \
    Loaders/fileloader.h \
    Loaders/idataloader.h \
    Loaders/networkloader.h \
    Loaders/sqlloader.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
