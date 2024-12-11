QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    doctoreditview.cpp \
    doctorview.cpp \
    drugeditview.cpp \
    drugview.cpp \
    idatabase.cpp \
    loginview.cpp \
    main.cpp \
    masterviw.cpp \
    medicalrecordview.cpp \
    patienteditview.cpp \
    patientview.cpp \
    welcomeview.cpp

HEADERS += \
    doctoreditview.h \
    doctorview.h \
    drugeditview.h \
    drugview.h \
    idatabase.h \
    loginview.h \
    masterviw.h \
    medicalrecordview.h \
    patienteditview.h \
    patientview.h \
    welcomeview.h

FORMS += \
    doctoreditview.ui \
    doctorview.ui \
    drugeditview.ui \
    drugview.ui \
    loginview.ui \
    masterviw.ui \
    medicalrecordview.ui \
    patienteditview.ui \
    patientview.ui \
    welcomeview.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    lab4.qrc
