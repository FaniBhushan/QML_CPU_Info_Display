import QtQuick 2.4
import QtQuick.Window 2.2

Window {
    visible: true
    width: 800
    height:600
    color: "#350820"
    title: qsTr("CPU Info")

    Component {
        id: showListDelegate
        Rectangle {
             height: 35
             width: parent.width
             color: "#350820"
             Text {
                height: 30
                width: parent.width
                color : "white"
                text: display
                wrapMode: Text.Wrap
            }
        }
    }

    ListView {
        id :listView
        width: parent.width
        height: parent.height
        model: listModel
        boundsBehavior : Flickable.StopAtBounds
        delegate: showListDelegate
    }
}


