import QtQuick 2.4

Item {
    id: scrollbar;
    width: handleSize;
    anchors.top: flickable.top
    anchors.bottom: flickable.bottom

    property Flickable flickable: null;
    property int handleSize: 20;

    Rectangle {
        id: backScrollbar;
        radius: 2;
        antialiasing: true;
        color: "transparent"
        anchors { fill: parent; }
    }

    Item {
        id: groove;
        clip: true;
        anchors.fill: parent

        Item {
            id: handle;
            height: Math.max (20, (flickable.visibleArea.heightRatio * groove.height));
            anchors {
                left: parent.left;
                right: parent.right;
            }

            Rectangle {
                id: backHandle
                color: "white"
                opacity: .8
                anchors.fill: parent
            }
        }
    }
}
