QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/files/filehandling.cpp \
    src/files/note.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/passworddialog.cpp \
    src/startupdialog.cpp \
    src/okcrypt/okcrypt.cpp \
    src/mrichtextedit.cpp \
    src/mtextedit.cpp

HEADERS += \
    src/files/filehandling.h \
    src/files/note.h \
    src/mainwindow.h \
    src/okcrypt/okcrypt.h \
    src/passworddialog.h \
    src/startupdialog.h \
    src/mrichtextedit.h \
    src/mtextedit.h

FORMS += \
    src/mainwindow.ui \
    src/passworddialog.ui \
    src/startupdialog.ui \
    src/mrichtextedit.ui

TRANSLATIONS += \
    SecNotes_en_US.ts
CONFIG += lrelease
CONFIG += embed_translations

OTHER_FILES += README.md

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    LICENSE
