import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2

ApplicationWindow {
    title: qsTr("PROJECTu")
    id: window
    width: 800
    height: 480
    visible: true

    Item {
        id: root
        anchors.fill: parent

        HomePage {
            id: home
            anchors.fill: root
            image: "../images/Lorde.jpg"
            playing: true
            focus: true
        }

        NowPlaying {
            id: nowPlaying
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            songName: "Royals"
            songArtist: "Lorde"
            songAlbum: "Pure Heroine"
            albumCover: "../images/Lorde.jpg"
            songDuration: 190
            songPlayed: 10
            repeatMode: 1
            shuffleMode: false
            play: true
            state: "hidden"
        }

        AddToPlaylist {
            id: addToPlaylist
            anchors.fill: root
            playlists: ["Party", "Quiet", "Study", "Coding", "Movies", "Victorious", "Modern", "Old Hits"]

            onAdded: {

            }

            onCreateNewPlaylist: {

            }
        }

        StatusBarTop {
            id: statusBar
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            isPlaying: true
            connectionType: 4
            opacity: 1
        }

        Keyboard {
            id: keyboard
            anchors.verticalCenter: parent.verticalCenter
            anchors.verticalCenterOffset: focus? 0 : 350
            anchors.horizontalCenter: parent.horizontalCenter

            Behavior on anchors.verticalCenterOffset {
                NumberAnimation {
                    duration: 250
                    easing.type: Easing.OutExpo
                }
            }

            onCanceled: {
                focus = false
            }
        }
    }
}
