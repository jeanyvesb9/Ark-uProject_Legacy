TEMPLATE = app

QT += qml quick widgets

SOURCES += src/database/album.cpp \
    src/database/library.cpp \
    src/database/playlist.cpp \
    src/database/song.cpp \
    src/dmap/dmapclient.cpp \
    src/applicationdata.cpp \
    src/main.cpp \
    src/dmap/dmap-parser.c \
    src/database/artist.cpp

CONFIG += c++14

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

DISTFILES += \
    qml/main.qml \
    qml/NowPlaying.qml \
    qml/StatusBarTop.qml \
    qml/HomePage.qml \
    qml/OptionMenuItem.qml \
    qml/ListMenu.qml \
    qml/AddToPlaylist.qml \
    qml/PlayFunctions.js \
    images/Album-Cover.png \
    images/Diagonal-Shine.png \
    images/Play.png \
    images/Progress.png \
    images/ProgressBar.png \
    images/Repeat.png \
    images/Reproduction-Marker.png \
    images/Shuffle.png \
    images/StatusBar-Play.png \
    images/TaylorSwift_Red.png \
    images/Wifi.png \
    qml/Keyboard.qml \
    qml/KeyboardItem.qml \
    qml/NewPlaylist.qml \
    images/HomeBackground.png \
    workingImages/HomeBackground.png \
    workingImages/PSD/HomeBackground.psd

HEADERS += src/database/album.h \
    src/database/library.h \
    src/database/playlist.h \
    src/database/song.h \
    src/dmap/dmap-parser.h \
    src/dmap/dmapclient.h \
    src/applicationdata.h \
    src/global.h \
    src/database/artist.h
