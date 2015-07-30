TEMPLATE = app

QT += qml quick widgets network

SOURCES += src/database/album.cpp \
    src/database/library.cpp \
    src/database/playlist.cpp \
    src/database/song.cpp \
    src/dmap/dmapclient.cpp \
    src/applicationdata.cpp \
    src/main.cpp \
    src/dmap/dmap-parser.c \
    src/database/artist.cpp \
    src/songview.cpp \
    src/dmap/dmapstatement.cpp

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
    workingImages/PSD/HomeBackground.psd \
    qml/AlbumPage.qml \
    images/Lorde.jpg \
    images/Arrow.png \
    images/Pause.png \
    images/PBar.png \
    images/ShiftArrow.png \
    images/ShiftLockedArrow.png \
    images/ShiftOnArrow.png \
    images/StatusBar-Ethernet.png \
    images/StatusBar-WiFi-H.png \
    images/StatusBar-WiFi-L.png \
    images/StatusBar-WiFi-M.png \
    images/StatusBar-WiFi-N.png \
    workingImages/Album-Cover.png \
    workingImages/Arrow.png \
    workingImages/Diagonal-Shine.png \
    workingImages/Pause.png \
    workingImages/Play.png \
    workingImages/Progress.png \
    workingImages/ProgressBar.png \
    workingImages/Repeat.png \
    workingImages/Reproduction-Marker.png \
    workingImages/ShiftArrow.png \
    workingImages/ShiftLockedArrow.png \
    workingImages/ShiftOnArrow.png \
    workingImages/Shuffle.png \
    workingImages/StatusBar-Ethernet.png \
    workingImages/StatusBar-Play.png \
    workingImages/StatusBar-WiFi-H.png \
    workingImages/StatusBar-WiFi-L.png \
    workingImages/StatusBar-WiFi-M.png \
    workingImages/StatusBar-WiFi-N.png \
    workingImages/TaylorSwift_Red.png \
    workingImages/WiFi.png \
    workingImages/PSD/Album-Cover.psd \
    workingImages/PSD/Arrow.psd \
    workingImages/PSD/Diagonal-Shine.psd \
    workingImages/PSD/Pause.psd \
    workingImages/PSD/Play.psd \
    workingImages/PSD/Progress.psd \
    workingImages/PSD/ProgressBar.psd \
    workingImages/PSD/Repeat.psd \
    workingImages/PSD/Reproduction-Marker.psd \
    workingImages/PSD/ShiftArrow.psd \
    workingImages/PSD/ShiftLockedArrow.psd \
    workingImages/PSD/ShiftOnArrow.psd \
    workingImages/PSD/Shuffle.psd \
    workingImages/PSD/StatusBar-Ethernet.psd \
    workingImages/PSD/StatusBar-Play.psd \
    workingImages/PSD/StatusBar-Wifi.psd

HEADERS += src/database/album.h \
    src/database/library.h \
    src/database/playlist.h \
    src/database/song.h \
    src/dmap/dmap-parser.h \
    src/dmap/dmapclient.h \
    src/applicationdata.h \
    src/global.h \
    src/database/artist.h \
    src/songview.h \
    src/dmap/dmapstatement.h
