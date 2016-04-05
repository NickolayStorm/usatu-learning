import QtQuick 2.0

Rectangle {
    width: 400
    height: 200

    TextInput {
        id: textInput1
        x: 114
        y: 44
        width: 117
        height: 20
        text: qsTr("")
        activeFocusOnPress: true
        font.pixelSize: 12
    }

    Text {
        id: text1
        x: 8
        y: 44
        width: 84
        height: 19
        text: qsTr("Логин")
        font.pixelSize: 12
    }

    Text {
        id: text2
        x: 8
        y: 78
        width: 84
        height: 21
        text: qsTr("Пароль")
        font.pixelSize: 12
    }

    TextInput {
        id: textInput2
        x: 114
        y: 79
        width: 117
        height: 20
        text: qsTr("")
        font.pixelSize: 12
    }

    Text {
        id: text3
        x: 271
        y: 78
        width: 121
        height: 21
        text: qsTr("Text")
        font.pixelSize: 12
    }
}

