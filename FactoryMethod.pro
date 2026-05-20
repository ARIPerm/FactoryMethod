QT += widgets core network sql

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Factory/fileloader.cpp \
    Factory/idataloader.cpp \
    Factory/networkloader.cpp \
    Factory/sqlloader.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Factory/fileloader.h \
    Factory/idataloader.h \
    Factory/networkloader.h \
    Factory/sqlloader.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
