import QtQuick 2.4
import QtQml 2.2
import QtGraphicalEffects 1.0
import "PlayFunctions.js" as PlayFunctions

Item {
    id: root
    width: 800; height: 480

    property string songName: ""
    property string songArtist: ""
    property string songAlbum: ""
    property string albumCover: ""
    property int songDuration: 0
    property int songPlayed: 0
    property int repeatMode: 0 // 0 = No ; 1 = On ; 2 = Song
    property bool shuffleMode: false
    property bool play
    property int menuSelected

    signal back()
    signal home()

    states: [
        State {
            name: "normal"
            PropertyChanges { target: songText; opacity: 1 }
            PropertyChanges { target: progressBarSection; opacity: 1 }
            PropertyChanges { target: optionMenu; width: 0 }
            PropertyChanges { target: backgroundBrightness; brightness: -0.25 }
        },

        State {
            name: "optionMenu"
            PropertyChanges { target: songText; opacity: 0 }
            PropertyChanges { target: progressBarSection; opacity: 0 }
            PropertyChanges { target: optionMenu; width: 451 }
            PropertyChanges { target: backgroundBrightness; brightness: -0.7 }
        }
    ]

    transitions: [
        Transition {
            id: normal_TO_optionMenu
            from: "normal"; to: "optionMenu"; reversible: false
            NumberAnimation {
                id: d
                target: backgroundBrightness
                properties: "brightness"
                duration: 300
                easing.type: Easing.OutExpo
            }
            NumberAnimation {
                id: dd
                target: optionMenu
                properties: "width"
                duration: 250
                easing.type: Easing.OutExpo
            }
        },

        Transition {
            id: optionMenu_TO_normal
            from: "optionMenu"; to: "normal"; reversible: false
            NumberAnimation {
                target: backgroundBrightness
                properties: "brightness"
                duration: 300
                easing.type: Easing.OutExpo
            }
            NumberAnimation {
                target: optionMenu
                properties: "width"
                duration: 250
                easing.type: Easing.OutExpo
            }
        }
    ]

    Keys.onReturnPressed: {
        if (state == "normal") {
            state = "optionMenu";
        }
        else if (state == "optionMenu") {
            switchMenuSelectedFocus();
        }
    }

    Keys.onEscapePressed: {
        if (state == "normal") {
            //pass
        }
        else if (state == "optionMenu") {
            state = "normal";
        }
    }

    Keys.onRightPressed: {
        if (state == "normal") {
            //pass
        }
        else if (state == "optionMenu") {
            if (menuSelected == 5) {
                //play sound
                //pass
            }
            else {
                menuSelected++;
            }
        }
    }

    Keys.onLeftPressed: {
        if (state == "normal") {
            //pass
        }
        else if (state == "optionMenu") {
            if (menuSelected == 0) {
                //play sound
                //pass
            }
            else {
                menuSelected--;
            }
        }
    }

    function switchMenuSelectedFocus() {
        switch (menuSelected) {
        case 0:
            optionMenuRepeat.focus = true;
            break;
        case 1:
            optionMenuShuffle.focus = true;
            break;
        case 2:
            optionMenuAddToPlaylist.focus = true;
            break;
        case 3:
            optionMenuHidden.focus = true;
            break;
        case 4:
            optionMenuEqualizer.focus = true;
            break;
        case 5:
            optionMenuFile.focus = true;
            break;
        }
    }

    Item {
        id: background
        anchors.centerIn: root
        width: 1250; height: 1167

        Image {
            id: backgroundImage
            anchors.fill: background
            source: albumCover
            smooth: true
        }

        GaussianBlur {
            id: backgroundBlur
            anchors.fill: background
            source: backgroundImage
            radius: 35
            deviation: 17
            samples: 33
            smooth: true
        }

        BrightnessContrast {
            id: backgroundBrightness
            anchors.fill: background
            source: backgroundBlur
            brightness: -0.25
            smooth: true
        }
    }

    Item {
        id: artwork
        width: 250; height: 250
        anchors.verticalCenter: root.verticalCenter
        anchors.left: root.left
        anchors.leftMargin: 50

        Image {
            id: artworkCover
            anchors.horizontalCenter: artwork.horizontalCenter
            anchors.verticalCenter: artwork.verticalCenter
            source: "../images/Album-Cover.png"
            smooth: true
        }

        Image {
            id: artworkImage
            anchors.fill: artwork
            source: albumCover
            smooth: true
        }

        Image {
            id: artworkDiagonalShine
            anchors.fill: artwork
            source: "../images/Diagonal-Shine.png"
            smooth: true
        }
    }

    Item {
        id: songText
        width: 440; height: 90
        anchors.left: root.left
        anchors.leftMargin: 340
        anchors.top: root.top
        anchors.topMargin: 115

        Text {
            id: uiSongName
            anchors.top: songText.top
            anchors.topMargin: -13
            anchors.left: songText.left
            font.family: "Segoe UI"
            font.weight: Font.Light
            font.pixelSize: 40
            color: "white"
            opacity: 0.8
            text: songName
            smooth: true
        }

        Text {
            id: uiSongArtist
            anchors.top: uiSongName.bottom
            anchors.topMargin: 4
            anchors.left: songText.left
            anchors.leftMargin: 2
            font.family: "Segoe UI Light"
            font.pixelSize:21
            font.bold: true
            color: "white"
            opacity: 0.5
            text: songArtist
            smooth: true
        }

        Text {
            id: uiSongAlbum
            anchors.top: uiSongArtist.bottom
            anchors.topMargin: -5
            anchors.left: songText.left
            anchors.leftMargin: 2
            font.family: "Segoe UI Light"
            font.pixelSize:21
            font.bold: true
            color: "white"
            opacity: 0.5
            text: songAlbum
            smooth: true
        }
    }

    Item {
        id: progressBarSection
        width: 440; height: 70
        anchors.top: root.top
        anchors.topMargin: 300
        anchors.left: artwork.right
        anchors.leftMargin: 40

        Image {
            id: playIcon
            anchors.top: progressBarSection.top
            anchors.left: progressBarSection.left
            anchors.leftMargin: 3
            source: "../images/Play.png"
            visible: play
            smooth: true
        }

        Image {
            id: pauseIcon
            anchors.top: progressBarSection.top
            anchors.left: progressBarSection.left
            anchors.leftMargin: 3
            source: "../images/Pause.png"
            visible: !play
            smooth: true
        }

        Text {
            id: uiSongPlayed
            anchors.top: progressBarSection.top
            anchors.topMargin: -10
            anchors.left: progressBarSection.left
            anchors.leftMargin: 32
            font.family: "Segoe UI Light"
            font.pixelSize: 21
            font.bold: true
            color: "white"
            text: PlayFunctions.calcSongPlayedString(songPlayed)
            smooth: true
        }

        Text {
            id: uiSongLeft
            anchors.top: progressBarSection.top
            anchors.topMargin: -10
            anchors.right: progressBarSection.right
            font.family: "Segoe UI Light"
            font.pixelSize: 21
            font.bold: true
            color: "white"
            text: PlayFunctions.calcSongRemString(songPlayed, songDuration)
            smooth: true
        }

        Rectangle {
            id: progressBar
            height: 6; width: 440
            anchors.verticalCenter: progressBarSection.verticalCenter
            anchors.verticalCenterOffset: -5.5
            anchors.horizontalCenter: progressBarSection.horizontalCenter
            smooth: true
            clip: true

            Image {
                id:progressBarBackground
                anchors.verticalCenter: progressBar.verticalCenter
                anchors.verticalCenterOffset: -90
                anchors.horizontalCenter: progressBar.horizontalCenter
                anchors.horizontalCenterOffset: -160
                width: 1250; height: 1167
                source: albumCover
                smooth: true
            }

            GaussianBlur {
                id: progressBarBackgroundBlur
                anchors.fill: progressBarBackground
                source: progressBarBackground
                radius: 45
                deviation: 20
                samples: 33
                smooth: true
            }

            Image {
                id: progress
                anchors.verticalCenter: progressBar.verticalCenter
                anchors.verticalCenterOffset: 1
                anchors.left: progressBar.left
                width: PlayFunctions.calcProgressBarPerc(songPlayed, songDuration)
                source: "../images/Progress.png"
                smooth: true
            }
        }

        Rectangle {
            id: reproductionMarker
            width: 3; height: 14
            anchors.left: progressBarSection.left
            anchors.leftMargin: PlayFunctions.calcProgressBarPerc(songPlayed, songDuration) - 1
            anchors.verticalCenter: progressBar.verticalCenter
            anchors.verticalCenterOffset: 1
            color: "white"
        }

        Item {
            id: shuffleRepeatIcons
            anchors.right: progressBarSection.right
            anchors.rightMargin: -22 //22
            anchors.bottom: progressBarSection.bottom
            anchors.bottomMargin: -30
            width: 150; height: 90

            Image {
                id: shuffleImage
                anchors.verticalCenter: shuffleRepeatIcons.verticalCenter
                anchors.left: shuffleRepeatIcons.left
                anchors.leftMargin: {
                    switch(repeatMode)
                    {
                    case 0:
                        return 5;
                    case 1:
                        return -10;
                    case 2:
                        return 0;
                    }
                }

                source: "../images/Shuffle.png"
                opacity: .6
            }

            Text {
                id: shuffleText
                anchors.verticalCenter: shuffleRepeatIcons.verticalCenter
                anchors.verticalCenterOffset: 0
                anchors.left: shuffleImage.right
                anchors.leftMargin: 4
                font.family: "Segoe UI Light"
                font.pixelSize: 15
                font.bold: true
                color: "white"
                text: { shuffleMode? "All" : "Off" }
                smooth: true
                opacity: .6
            }

            Image {
                id: repeatImage
                anchors.verticalCenter: shuffleRepeatIcons.verticalCenter
                anchors.right: repeatText.left
                anchors.rightMargin: 4
                source: "../images/Repeat.png"
                opacity: .6
            }

            Text {
                id: repeatText
                anchors.verticalCenter: shuffleRepeatIcons.verticalCenter
                anchors.verticalCenterOffset: 0
                anchors.right: shuffleRepeatIcons.right
                anchors.rightMargin: 23
                font.family: "Segoe UI Light"
                font.pixelSize: 15
                font.bold: true
                color: "white"
                text: {
                    switch(repeatMode)
                    {
                    case 0:
                        return "Off";
                    case 1:
                        return "Album";
                    case 2:
                        return "Song";
                    }
                }
                smooth: true
                opacity: .6
            }
        }
    }

    Item {
        id: optionMenu
        anchors.right: root.right
        anchors.top: root.top
        anchors.bottom: root.bottom
        width: 451

        Rectangle {
            id: optionMenuBackground
            anchors.fill: optionMenu
            color: "Black"
            smooth: true
            opacity: .72
        }

        Rectangle {
            id: optionMenuSideLine
            anchors.left: optionMenu.left
            anchors.top: optionMenuBackground.top
            anchors.bottom: optionMenuBackground.bottom
            width: 5
            smooth: true
            clip: true

            Image {
                id: optionMenuSideLineImage
                anchors.verticalCenter: optionMenuSideLine.verticalCenter
                anchors.horizontalCenter: optionMenuSideLine.horizontalCenter
                anchors.horizontalCenterOffset: 48.5
                width: 1250; height: 1167
                source: albumCover
                smooth: true
            }

            GaussianBlur {
                id: optionMenuSideLineBlur
                anchors.fill: optionMenuSideLineImage
                source: optionMenuSideLineImage
                radius: 45
                deviation: 20
                samples: 33
                smooth: true
            }
        }

        Rectangle {
            id: optionMenuSelected
            anchors.top: optionMenu.top
            anchors.topMargin: 97 + 48 * menuSelected
            anchors.left: optionMenu.left
            anchors.leftMargin: 5
            width: 446; height: 46
            clip: true

            Image {
                id: optionMenuSelectedImage
                anchors.verticalCenter: optionMenuSelected.verticalCenter
                anchors.verticalCenterOffset: {
                    switch(menuSelected)
                    {
                    case 0:
                        return 120;
                    case 1:
                        return 72;
                    case 2:
                        return 24;
                    case 3:
                        return -24;
                    case 4:
                        return -72;
                    case 5:
                        return -120;
                    }
                }

                anchors.horizontalCenter: optionMenuSelected.horizontalCenter
                anchors.horizontalCenterOffset: -176.5
                width: 1250; height: 1167
                source: albumCover
                smooth: true
            }

            GaussianBlur {
                id: optionMenuSelectedBlur
                anchors.fill: optionMenuSelectedImage
                source: optionMenuSelectedImage
                radius: 45
                deviation: 20
                samples: 33
                smooth: true
            }
        }

        OptionMenuItem {
            id: optionMenuRepeat
            anchors.top: optionMenu.top
            anchors.topMargin: 96
            anchors.left: optionMenu.left
            anchors.leftMargin: 5
            width: 446; height: 48
            mainText: "Repeat"
            options: ["Off", "Album", "Song"]
            optionSelected: repeatMode
            displayOption: true
            displayHorizontalMenu: true

            onOptionSelectedChanged: {
                repeatMode = optionSelected
            }
        }

        OptionMenuItem {
            id: optionMenuShuffle
            anchors.top: optionMenuRepeat.bottom
            anchors.left: optionMenu.left
            anchors.leftMargin: 5
            width: 446; height: 48
            mainText: "Shuffle"
            options: ["Off", "All"]
            optionSelected: shuffleMode
            displayOption: true
            displayHorizontalMenu: true

            onOptionSelectedChanged: {
                shuffleMode = optionSelected
            }
        }

        OptionMenuItem {
            id: optionMenuAddToPlaylist
            anchors.top: optionMenuShuffle.bottom
            anchors.left: optionMenu.left
            anchors.leftMargin: 5
            width: 446; height: 48
            mainText: "Add to Playlist"

            onFocusChanged: {
                if (focus) { addToPlaylist.focus = true; }
            }
        }

        OptionMenuItem {
            id: optionMenuHidden
            anchors.top: optionMenuAddToPlaylist.bottom
            anchors.left: optionMenu.left
            anchors.leftMargin: 5
            width: 446; height: 48
            mainText: "Hidden"
        }

        OptionMenuItem {
            id: optionMenuEqualizer
            anchors.top: optionMenuHidden.bottom
            anchors.left: optionMenu.left
            anchors.leftMargin: 5
            width: 446; height: 48
            mainText: "Equalizer"
        }

        OptionMenuItem {
            id: optionMenuFile
            anchors.top: optionMenuEqualizer.bottom
            anchors.left: optionMenu.left
            anchors.leftMargin: 5
            width: 446; height: 48
            mainText: "File"
        }
    }

    ListMenu {
        id: addToPlaylist
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.rightMargin: -800
        width: 800
        title: "Add to Playlist"
        subtitle: "Subtitle is like this, it goes right here!"
        options: ["Party", "Quiet", "Study", "Coding", "Movies", "Victorious", "Modern", "Old Hits", "Happy"]
        showDescription: true

        Behavior on anchors.rightMargin {
            NumberAnimation { duration: 250; easing.type: Easing.OutExpo }
        }

        onFocusChanged: {
            if (focus) {
                anchors.rightMargin = 0;
            }
            else {
                anchors.rightMargin = -800;

            }
        }
    }

}
