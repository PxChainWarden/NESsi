import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import testPackage 1.0

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    TestClass{
        id: testClass
    }

    Button {
        id: clock_button
        width: 88
        height: 30
        anchors.centerIn: parent
        text: qsTr("Clock")
        icon.color: "#d80c0c0c"
        onClicked: testClass.activateClock()
    }

    Text{
        id: accumulator_value
        anchors{
            top: parent.top
            right: parent.horizontalCenter
            rightMargin: 70
            topMargin: 20
        }
        font.pixelSize: 16
        text: testClass.accumulator
    }
    Text{
        id: accumulator_label
        anchors{
            top: parent.top
            left: parent.left
            topMargin: 20
        }
        font.pixelSize: 16
        text: "Accumulator: "
    }
    Text{
        id: program_counter_value
        anchors{
            top: parent.top
            right: parent.horizontalCenter
            rightMargin: 70
            topMargin: 40
        }
        font.pixelSize: 16
        text: testClass.pc
    }
    Text{
        id: program_counter_label
        anchors{
            top: parent.top
            left: parent.left
            topMargin: 40
        }
        font.pixelSize: 16
        text: "Program Counter: "
    }
    Text{
        id: x_value
        anchors{
            top: parent.top
            right: parent.horizontalCenter
            rightMargin: 70
            topMargin: 60
        }
        font.pixelSize: 16
        text: testClass.x
    }
    Text{
        id: x_label
        anchors{
            top: parent.top
            left: parent.left
            topMargin: 60
        }
        font.pixelSize: 16
        text: "X Register: "
    }
    Text{
        id: y_value
        anchors{
            top: parent.top
            right: parent.horizontalCenter
            rightMargin: 70
            topMargin: 80
        }
        font.pixelSize: 16
        text: testClass.y
    }
    Text{
        id: y_label
        anchors{
            top: parent.top
            left: parent.left
            topMargin: 80
        }
        font.pixelSize: 16
        text: "Y Register: "
    }
    Text{
        id: status_value
        anchors{
            top: parent.top
            right: parent.horizontalCenter
            rightMargin: 70
            topMargin: 100
        }
        font.pixelSize: 16
        text: testClass.status
    }
    Text{
        id: status_label
        anchors{
            top: parent.top
            left: parent.left
            topMargin: 100
        }
        font.pixelSize: 16
        text: "Status Register: "
    }
    Text{
        id: status_flags
        anchors{
            top: parent.top
            right: parent.horizontalCenter
            rightMargin: 70
            topMargin: 120
        }
        font.pixelSize: 16
        text: "NVUBDIZC"
    }
    Text{
        id: opcode_value
        anchors{
            top: parent.top
            right: parent.horizontalCenter
            rightMargin: 70
            topMargin: 140
        }
        font.pixelSize: 16
        text: testClass.opcode
    }
    Text{
        id: opcode_label
        anchors{
            top: parent.top
            left: parent.left
            topMargin: 140
        }
        font.pixelSize: 16
        text: "Instruction: "
    }

    Column {
        id: column
        anchors{
            top: parent.top
            right: parent.right
        }
        width: 200
        height: 400

        Repeater {
            id: repeater
        }
    }

}
