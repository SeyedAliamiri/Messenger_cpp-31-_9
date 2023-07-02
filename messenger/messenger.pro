QT       += core gui
QT       +=  network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    channel.cpp \
    chat.cpp \
    create_channel_group.cpp \
    group.cpp \
    join_channel_group.cpp \
    log_in.cpp \
    main.cpp \
    main_page.cpp \
    main_user.cpp \
    mainwindow.cpp \
    sign_in.cpp \
    user.cpp

HEADERS += \
    channel.h \
    chat.h \
    create_channel_group.h \
    group.h \
    join_channel_group.h \
    log_in.h \
    main_page.h \
    main_user.h \
    mainwindow.h \
    sign_in.h \
    user.h

FORMS += \
    create_channel_group.ui \
    join_channel_group.ui \
    log_in.ui \
    main_page.ui \
    mainwindow.ui \
    sign_in.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

QMAKE_CXXFLAGS += -std=gnu++11
