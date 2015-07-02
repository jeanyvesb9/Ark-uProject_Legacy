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
        }

        NowPlaying {
            id: nowPlaying
            anchors.fill: root
            songName: "Begin Again"
            songArtist: "Taylor Swift ft. Ed Sheeran"
            songAlbum: "Red"
            albumCover: "../images/TaylorSwift_Red.png"
            songDuration: 229
            songPlayed: 10
            repeatMode: 1
            shuffleMode: false
            play: true
            state: "normal"
            focus: false
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
            anchors.top: nowPlaying.top
            anchors.right: nowPlaying.right
            isPlaying: true
            connectionType: 4
            opacity: 0
        }

        Keyboard {
            id: keyboard
            anchors.verticalCenter: parent.verticalCenter
            anchors.verticalCenterOffset:  0
            anchors.horizontalCenter: parent.horizontalCenter
            inputText: ""
            focus: true
        }
    }
}
