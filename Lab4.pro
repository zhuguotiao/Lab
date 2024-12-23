QT       += core gui sql network concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# Add the library headers and include paths
INCLUDEPATH += $$PWD/../../SmtpClient-for-Qt-2.0/src

# Add the library path for linking (DLL or static library)
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../SmtpClient-for-Qt-2.0/src/build/Desktop_Qt_6_7_2_MinGW_64_bit-Debug/release/ -lSmtpMime2
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../SmtpClient-for-Qt-2.0/src/build/Desktop_Qt_6_7_2_MinGW_64_bit-Debug/debug/ -lSmtpMime2
else:unix: LIBS += -L$$PWD/../../SmtpClient-for-Qt-2.0/src/build/Desktop_Qt_6_7_2_MinGW_64_bit-Debug/ -lSmtpMime2

# Ensure the correct path for the dependent files
DEPENDPATH += $$PWD/../../SmtpClient-for-Qt-2.0/src/build/Desktop_Qt_6_7_2_MinGW_64_bit-Debug/debug

# Add your project source and header files
SOURCES += \
    doctoreditview.cpp \
    doctorview.cpp \
    drugeditview.cpp \
    drugview.cpp \
    idatabase.cpp \
    loginview.cpp \
    main.cpp \
    masterviw.cpp \
    medicalrecordeditview.cpp \
    medicalrecordview.cpp \
    patienteditview.cpp \
    patientreserveview.cpp \
    patientview.cpp \
    reserveeditview.cpp \
    reserveview.cpp \
    welcomeview.cpp

HEADERS += \
    doctoreditview.h \
    doctorview.h \
    drugeditview.h \
    drugview.h \
    idatabase.h \
    loginview.h \
    masterviw.h \
    medicalrecordeditview.h \
    medicalrecordview.h \
    patienteditview.h \
    patientreserveview.h \
    patientview.h \
    reserveeditview.h \
    reserveview.h \
    welcomeview.h

FORMS += \
    doctoreditview.ui \
    doctorview.ui \
    drugeditview.ui \
    drugview.ui \
    loginview.ui \
    masterviw.ui \
    medicalrecordeditview.ui \
    medicalrecordview.ui \
    patienteditview.ui \
    patientreserveview.ui \
    patientview.ui \
    reserveeditview.ui \
    reserveview.ui \
    welcomeview.ui

# Include resources
RESOURCES += \
    lab4.qrc

# Deployment rules
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
