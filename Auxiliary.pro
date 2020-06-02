QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

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
    classify.cpp \
    control.cpp \
    counter.cpp \
    delay.cpp \
    hotkey.cpp \
    main.cpp \
    mainwindow.cpp \
    match.cpp \
    operations.cpp \
    prompt.cpp \
    yuhun.cpp

HEADERS += \
    Auxiliary.rc \
    classify.h \
    config.h \
    control.h \
    counter.h \
    delay.h \
    hotkey.h \
    mainwindow.h \
    match.h \
    operations.h \
    prompt.h \
    yuhun.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32-g++:INCLUDEPATH += D:/installfile/OpenCV/MinGW/include
win32-g++:INCLUDEPATH += D:/installfile/OpenCV/MinGW/include/opencv
win32-g++:INCLUDEPATH += D:/installfile/OpenCV/MinGW/include/opencv2
else:win32:!win32-g++:INCLUDEPATH += D:/installfile/OpenCV/MSVC/include
else:win32:!win32-g++:INCLUDEPATH += D:/installfile/OpenCV/MSVC/include/opencv
else:win32:!win32-g++:INCLUDEPATH += D:/installfile/OpenCV/MSVC/include/opencv2

INCLUDEPATH += C:/Program Files (x86)/Windows Kits/10/Include/10.0.14393.0/um

win32-g++:LIBS += D:/installfile/OpenCV/MinGW/x64/mingw/lib/libopencv*.dll.a
else:win32:!win32-g++:LIBS += D:/installfile/OpenCV/MSVC/x64/vc14/lib/opencv*.lib

DEFINES-= UNICODE

RESOURCES += \
    imgresource.qrc

RC_FILE = Auxiliary.rc

DISTFILES += \
    Auxiliary.exe.manifest
