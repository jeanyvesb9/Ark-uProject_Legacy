import QtQuick 2.0

Item {
    id: root
    width: 800; height: 480
    property string from

    Keys.onEscapePressed: {
        if(state == "normal") {
            home.focus = true;
            state = "hidden";
        }
    }

    Keys.onLeftPressed: {
        songView.decrementCurrentIndex()
        songView.positionViewAtIndex(songView.currentIndex, ListView.Visible);
    }
    Keys.onRightPressed: {
        songView.incrementCurrentIndex()
        songView.positionViewAtIndex(songView.currentIndex, ListView.Contain);
    }

    onFocusChanged: {
        if(focus) {
            switch(from) {
            case "home":
                songView.highlightMoveDuration = 0;
                songView.currentIndex = 0;
                songView.highlightMoveDuration = -1;
            }
        }
    }

    states: [
        State {
            name: "hidden"
            PropertyChanges { target:root; anchors.horizontalCenterOffset: 800 }
        },

        State {
            name: "normal"
            PropertyChanges { target: root; anchors.horizontalCenterOffset: 0 }
        }
    ]

    transitions: [
        Transition {
            id: normal_to_hidden
            from: "normal"; to: "hidden"; reversible: false
            NumberAnimation {
                target: root
                properties: "anchors.horizontalCenterOffset"
                duration: 300
                easing.type: Easing.OutExpo
            }
        },

        Transition {
            id: hidden_to_normal
            from: "hidden"; to: "normal"; reversible: false
            NumberAnimation {
                target: root
                properties: "anchors.horizontalCenterOffset"
                duration: 300
                easing.type: Easing.OutExpo
            }
        }

    ]

    Rectangle {
        id: background
        width:800; height: 480
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        color: "black" //"#282828"
    }

    Text {
        id: homeText
        anchors.top: parent.top
        anchors.topMargin: 15
        anchors.left: parent.left
        anchors.leftMargin: 33
        font.family: "Segoe UI Light"
        font.bold: true
        font.pixelSize: 35
        color: "white"
        text: "Songs"
    }

    Rectangle {
        id: songViewColumn
        anchors.right: parent.right
        anchors.rightMargin: 20
        y: 85 + songView.visibleArea.yPosition * songView.height
        width: 10
        height: songView.visibleArea.heightRatio * songView.height
        color: "black"
        opacity: .75
    }

    ListModel {
        id: listModel

        ListElement {
            name: "A World Alone"
            album: "Pure Heroine"
            artist: "Lorde"
        }
        ListElement {
            name: "Buzzcut Season"
            album: "Pure Heroine"
            artist: "Lorde"
        }
        ListElement {
            name: "Glory and Gore"
            album: "Pure Heroine"
            artist: "Lorde"
        }
        ListElement {
            name: "Ribs"
            album: "Pure Heroine"
            artist: "Lorde"
        }
        ListElement {
            name: "Royals"
            album: "Pure Heroine"
            artist: "Lorde"
        }
        ListElement {
            name: "Still Sane"
            album: "Pure Heroine"
            artist: "Lorde"
        }
        ListElement {
            name: "Team"
            album: "Pure Heroine"
            artist: "Lorde"
        }
        ListElement {
            name: "Tennis Court"
            album: "Pure Heroine"
            artist: "Lorde"
        }
        ListElement {
            name: "White Teeth Teens"
            album: "Pure Heroine"
            artist: "Lorde"
        }
        ListElement {
            name: "State Of Grace"
            album: "Red"
            artist: "Taylor Swift"
        }
        ListElement {
            name: "Red"
            album: "Red"
            artist: "Taylor Swift"
        }
        ListElement {
            name: "Treacherous"
            album: "Red"
            artist: "Taylor Swift"
        }
        ListElement {
            name: "I Knew You Were Trouble"
            album: "Red"
            artist: "Taylor Swift"
        }
        ListElement {
            name: "All Too Well"
            album: "Red"
            artist: "Taylor Swift"
        }
        ListElement {
            name: "22"
            album: "Red"
            artist: "Taylor Swift"
        }
        ListElement {
            name: "I Almost Do"
            album: "Red"
            artist: "Taylor Swift"
        }
        ListElement {
            name: "We Are Never Ever Getting Back Together"
            album: "Red"
            artist: "Taylor Swift"
        }
        ListElement {
            name: "Stay Stay Stay"
            album: "Red"
            artist: "Taylor Swift"
        }
    }

    Component {
        id: delegate

        Item {
            id: delegateRoot
            width: 750; height: 60
            Component.onCompleted: console.log("created" + index) //LOADIMAGE
            Component.onDestruction: console.log("destroyed" + index)
            Rectangle {
                id: delegateBackground
                anchors.fill: parent
                color: delegateRoot.ListView.isCurrentItem? "white" : "transparent"
                opacity: 1
            }
            Rectangle {
                id: image
                anchors.left: parent.left; anchors.leftMargin: 3
                anchors.top: parent.top; anchors.topMargin: 3
                anchors.bottom: parent.bottom; anchors.bottomMargin: 3
                width: 54; color: "red"
            }
            Text {
                id: songName
                anchors.left: image.right
                anchors.leftMargin: 20
                anchors.top: parent.top
                anchors.topMargin: 1
                font.family: "Segoe UI"
                font.weight: Font.Light
                font.pixelSize: 25
                font.bold: true
                color: delegateRoot.ListView.isCurrentItem? "black" : "white"
                opacity: 0.8
                text: name
            }
            Text {
                id: songArtist
                anchors.left: image.right
                anchors.leftMargin: 20
                anchors.top: parent.top
                anchors.topMargin: 32
                font.family: "Segoe UI"
                font.weight: Font.Light
                font.pixelSize: 17
                font.bold: true
                color: delegateRoot.ListView.isCurrentItem? "black" : "white"
                opacity: 0.8
                text: artist
            }
            Text {
                id: songAlbum
                anchors.left: songArtist.right
                anchors.leftMargin: 5
                anchors.top: parent.top
                anchors.topMargin: 32
                font.family: "Segoe UI Light"
                font.pixelSize: 17
                font.bold: false
                color: delegateRoot.ListView.isCurrentItem? "black" : "white"
                opacity: 0.8
                text: album
            }
        }
    }

    Component {
        id: sectionDelegate
        Item {
            id: sectionDelegateRoot
            width: 750
            height: 30
            Rectangle {
                anchors.fill: parent
                color: "white"
                opacity: .75
                Text {
                    anchors.left: parent.left
                    anchors.leftMargin: 10
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.verticalCenterOffset: 0
                    font.family: "Segoe UI"
                    font.pixelSize: 17
                    font.bold: true
                    color: "black"
                    text: section
                }
            }
        }
    }

    ListView {
        id: songView
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.top: parent.top
        anchors.topMargin: 85
        width: 750; height: 380
        clip: true
        model: listModel
        delegate: delegate
        cacheBuffer: 60
        section.property: "name"
        section.criteria: ViewSection.FirstCharacter
        section.delegate: sectionDelegate
    }
}
