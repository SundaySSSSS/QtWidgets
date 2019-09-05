#-------------------------------------------------
#
# Project created by QtCreator 2019-01-07T21:49:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtWidgets
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    RangeSelectWidget/RangeSelectTestWidget.cpp \
    RangeSelectWidget/RangeSelectWidget.cpp \
    IPAddressWidget/IPAddressWidget.cpp \
    IPAddressWidget/IPAddressTest.cpp \
    ToastWidget/Toast.cpp

HEADERS  += widget.h \
    RangeSelectWidget/RangeSelectTestWidget.h \
    RangeSelectWidget/RangeSelectWidget.h \
    IPAddressWidget/IPAddressWidget.h \
    IPAddressWidget/IPAddressTest.h \
    ToastWidget/Toast.h

FORMS    += widget.ui \
    RangeSelectWidget/RangeSelectTestWidget.ui
