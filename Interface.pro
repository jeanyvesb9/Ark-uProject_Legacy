TEMPLATE = app

QT += qml quick widgets

SOURCES += main.cpp

CONFIG += c++14

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

DISTFILES += \
    qml/main.qml \
    qml/NowPlaying.qml \
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
    qml/StatusBarTop.qml \
    qml/PlayFunctions.js \
    qml/HomePage.qml \
    qml/OptionMenuItem.qml
