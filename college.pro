QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Include OpenXLSX headers
# INCLUDEPATH += "OpenXLSX/install/include"

# Link OpenXLSX library
# LIBS += -LOpenXLSX/build/Release -lOpenXLSX

# INCLUDEPATH += "OpenXLSX/install/include/OpenXLSX/headers"
# INCLUDEPATH += "OpenXLSX"


SOURCES += \
    collegedistances.cpp \
    listsouvenirs.cpp \
    login.cpp \
    main.cpp \
    maintenance.cpp \
    mainwindow.cpp \
    purchasesouvenirs.cpp \
    reguser.cpp \
    tripdisplay.cpp \
    tripplanning.cpp \
    utility.cpp

HEADERS += \
    collegedistances.h \
    listsouvenirs.h \
    login.h \
    main.h \
    maintenance.h \
    mainwindow.h \
    mergedtableview.h \
    purchasesouvenirs.h \
    reguser.h \
    tripdisplay.h \
    tripplanning.h \
    utility.h

FORMS += \
    collegedistances.ui \
    listsouvenirs.ui \
    login.ui \
    maintenance.ui \
    mainwindow.ui \
    purchasesouvenirs.ui \
    reguser.ui \
    tripdisplay.ui \
    tripplanning.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target



RESOURCES += \
    resource.qrc
