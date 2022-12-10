# Created by and for Qt Creator This file was created for editing the project sources only.
# You may attempt to use it for building too, by modifying this file here.
QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets gui charts

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

#TARGET = TP3_GestionEtu
SRCDIR=TP3_GestionEtu

HEADERS = \
   TP3_GestionEtu.h \
   controllers.h \
   observer.h \
   promotion.h \
   student.h \
   viewForms.h \
   viewHistogram.h \
   viewList.h \
   viewPieChart.h

SOURCES = \
   TP3_GestionEtu.cpp \
   main.cpp \
   promotion.cpp \
   student.cpp \
   viewForms.cpp \
   viewHistogram.cpp \
   viewList.cpp \
   viewPieChart.cpp

FORMS += \
    $$PWD/TP3_GestionEtu.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    $$PWD/TP3_GestionEtu.qrc

INCLUDEPATH = \
    $$PWD/.

#DEFINES = 

