import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import testPackage 1.0

Window {
    id: window
    width: 1024
    height: 960
    visible: true
    title: qsTr("NESsi")

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
        x: 168
        anchors{
            top: parent.top
            right: parent.horizontalCenter
            rightMargin: 170
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
        x: 237
        anchors{
            top: parent.top
            right: parent.horizontalCenter
            rightMargin: 170
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
        x: 247
        anchors{
            top: parent.top
            right: parent.horizontalCenter
            rightMargin: 170
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
        x: 248
        anchors{
            top: parent.top
            right: parent.horizontalCenter
            rightMargin: 170
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
        id: sp_value
        x: 238
        anchors{
            top: parent.top
            right: parent.horizontalCenter
            rightMargin: 170
            topMargin: 100
        }
        font.pixelSize: 16
        text: testClass.sp
    }
    Text{
        id: sp_label
        anchors{
            top: parent.top
            left: parent.left
            topMargin: 100
        }
        font.pixelSize: 16
        text: "Stack Pointer: "
    }
    Text{
        id: status_value
        x: 212
        anchors{
            top: parent.top
            right: parent.horizontalCenter
            rightMargin: 170
            topMargin: 120
        }
        font.pixelSize: 16
        text: testClass.status
    }
    Text{
        id: status_label
        anchors{
            top: parent.top
            left: parent.left
            topMargin: 120
        }
        font.pixelSize: 16
        text: "Status Register: "
    }
    Text{
        id: status_flags
        x: 264
        anchors{
            top: parent.top
            right: parent.horizontalCenter
            rightMargin: 170
            topMargin: 135
        }
        font.pixelSize: 16
        text: "NVUBDIZC"
    }
    Text{
        id: clock_value
        x: 218
        anchors{
            top: parent.top
            right: parent.horizontalCenter
            rightMargin: 170
            topMargin: 160
        }
        font.pixelSize: 16
        text: testClass.clock
    }
    Text{
        id: clock_label
        anchors{
            top: parent.top
            left: parent.left
            topMargin: 160
        }
        font.pixelSize: 16
        text: "Total Cycles: "
    }
    Text{
        id: opcode_value
        x: 202
        anchors{
            top: parent.top
            right: parent.horizontalCenter
            rightMargin: 170
            topMargin: 180
        }
        font.pixelSize: 16
        text: testClass.opcode
    }
    Text{
        id: opcode_label
        anchors{
            top: parent.top
            left: parent.left
            topMargin: 180
        }
        font.pixelSize: 16
        text: "Instruction: "
    }

    Canvas{
        id: canvas_screen
        focus: true
        width: 600
        height: 450
        anchors.verticalCenterOffset: -255
        anchors.horizontalCenterOffset: 212
        z: 1
        onPaint: {
            var context = getContext("2d");
            // Make canvas all white
            context.beginPath();
            context.clearRect(0, 0, width, height);



            var ar = context.getImageData(0,0,256,240);

            var frame = testClass.frame

            console.log(frame[0]);

            for(var i = 0; i < ar.data.length; i+=4){
//                console.log(palette);
                ar.data[i] = frame[i/4].r;
                ar.data[i+1] = frame[i/4].g;
                ar.data[i+2] = frame[i/4].b;
                ar.data[i+3] = frame[i/4].a;

            }
            context.drawImage(ar,0,0,width,height);
        }
        anchors{
            horizontalCenter: parent.horizontalCenter
            verticalCenter: parent.verticalCenter
        }
        Keys.onPressed: (event)=>{
            if(event.key === Qt.Key_A){
                var palette = testClass.changePalette
                canvas_pattern_table_left.requestPaint()
                canvas_pattern_table_right.requestPaint()
                console.log("Wololoo");
            }
            if(event.key === Qt.Key_F){
                canvas_screen.requestPaint()
            }

        }
    }

    Canvas{
        id: canvas_pattern_table_left
        width: 256
        height: 256
        anchors.verticalCenterOffset: 176
        anchors.horizontalCenterOffset: 91
        z: 1
        onPaint: {
            var context = getContext("2d");
            // Make canvas all white
            context.beginPath();
            context.clearRect(0, 0, width, height);



            var ar = context.getImageData(0,0,128,128);

            var frame = testClass.patternLeft


            for(var i = 0; i < ar.data.length; i+=4){
//                console.log(palette);
                ar.data[i] = frame[i/4].r;
                ar.data[i+1] = frame[i/4].g;
                ar.data[i+2] = frame[i/4].b;
                ar.data[i+3] = frame[i/4].a;

            }
            context.drawImage(ar,0,0,width,height);
        }
        anchors{
            horizontalCenter: parent.horizontalCenter
            verticalCenter: parent.verticalCenter
        }
    }

    Canvas{
        id: canvas_pattern_table_right
        width: 256
        height: 256
        anchors.verticalCenterOffset: 176
        anchors.horizontalCenterOffset: 384
        z: 1
        onPaint: {
            var context = getContext("2d");
            // Make canvas all white
            context.beginPath();
            context.clearRect(0, 0, width, height);



            var ar = context.getImageData(0,0,128,128);

            var frame = testClass.patternRight

            console.log(frame[0]);

            for(var i = 0; i < ar.data.length; i+=4){
//                console.log(palette);
                ar.data[i] = frame[i/4].r;
                ar.data[i+1] = frame[i/4].g;
                ar.data[i+2] = frame[i/4].b;
                ar.data[i+3] = frame[i/4].a;

            }
            context.drawImage(ar,0,0,width,height);
        }
        anchors{
            horizontalCenter: parent.horizontalCenter
            verticalCenter: parent.verticalCenter
        }
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
