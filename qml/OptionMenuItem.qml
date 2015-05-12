import QtQuick 2.4

Item {
    id: root
    width: 446; height: 48
    property alias mainText: mainText.text
    property bool displayOption
    property bool displayHorizontalMenu
    property bool displayListMenu
    property var options: []
    property int optionSelected
    property int tempOption
    property bool __displayOptionMenu

    signal callOptionWindow();

    onFocusChanged: {
        if (displayHorizontalMenu || displayListMenu) {
            __displayOptionMenu = !__displayOptionMenu;
        }
    }

    Keys.onEscapePressed: {
        parent.focus = true;
    }

    Keys.onLeftPressed: {

    }

    Keys.onRightPressed: {

    }

    Item {
        anchors.top: parent.top
        anchors.topMargin: 1
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 1
        anchors.left: parent.left
        anchors.right: parent.right

        Text {
            id: mainText
            anchors.verticalCenter: parent.verticalCenter
            anchors.verticalCenterOffset: -3
            anchors.left: parent.left
            anchors.leftMargin: 50
            font.family: "Segoe UI Light"
            font.pixelSize: 24
            font.bold: false
            color: "white"
            smooth: true
        }

        Text {
            id: currentOptionText
            anchors.verticalCenter: parent.verticalCenter
            anchors.verticalCenterOffset: -1
            anchors.right: parent.right
            anchors.rightMargin: 59
            font.family: "Segoe UI Light"
            font.pixelSize: 18
            font.bold: true
            color: "White"
            text: displayOption && !__displayOptionMenu? options[optionSelected] : ""
            smooth: true
        }

        Image {
            id: arrow
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: 21
            source: "../images/Arrow.png"
            opacity: __displayOptionMenu? 0: .25
            smooth: true
        }

        Item {
            id: hOptionMenu
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            anchors.rightMargin: __displayOptionMenu && displayHorizontalMenu? 0 : -273
            width: 91 * options.lenght

            Rectangle {
                id: hOptionMenuBackground
                anchors.fill: hOptionMenu
                color: "black"
                opacity: .5
            }

            Rectangle {
                id: hOptionMenuSelected
                anchors.top: hOptionMenu.top
                anchors.bottom: hOptionMenu.bottom
                anchors.right: hOptionMenu.right
                width: 91
                color: "black"
                opacity: .55
                border.color: "white"
                border.width: 2
            }
        }
    }
}
