QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17, console

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Particles/particle.cpp \
    bullet.cpp \
    enemy.cpp \
    game.cpp \
    level1.cpp \
    main.cpp \
    player.cpp \
    tower.cpp

HEADERS += \
    Particles/particle.h \
    bullet.h \
    enemy.h \
    game.h \
    level1.h \
    player.h \
    tower.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
