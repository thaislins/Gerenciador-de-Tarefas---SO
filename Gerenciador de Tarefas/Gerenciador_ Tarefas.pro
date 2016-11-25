#-------------------------------------------------
#
# Project created by QtCreator 2016-11-05T17:09:55
#
#-------------------------------------------------

QT       += core gui webenginewidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = SystemMonitor
TEMPLATE = app

SOURCES += main.cpp \
           gerenciador_tarefas.cpp \
           qcustomplot.cpp \
    dischargetime.cpp \
    batterypercentage.cpp \
    memoryinfo.cpp \
    cpuinfo.cpp \
    process.cpp

HEADERS  += gerenciador_tarefas.h \
            qcustomplot.h \
    dischargetime.h \
    batterypercentage.h \
    memoryinfo.h \
    cpuinfo.h \
    process.h

FORMS    += gerenciador_tarefas.ui
