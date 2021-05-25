QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    gameLogic/gamelogic.cpp \
    gameObjects/character.cpp \
    gameObjects/dynamicentity.cpp \
    gameObjects/player.cpp \
    gameObjects/staticentity.cpp \
    gameObjects/wall.cpp \
    main.cpp \
    gameObjects/entity.cpp \
    scenes/scene.cpp \
    scenes/gamescene.cpp \
    views/gamewindow.cpp

HEADERS += \
    gameLogic/gamelogic.h \
    gameObjects/character.h \
    gameObjects/dynamicentity.h \
    gameObjects/entity.h \
    gameObjects/player.h \
    gameObjects/staticentity.h \
    gameObjects/wall.h \
    scenes/scene.h \
    scenes/gamescene.h \
    views/gamewindow.h \
    views/observer.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    sprites.qrc
