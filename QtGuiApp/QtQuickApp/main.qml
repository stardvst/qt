import QtQuick 2.11
import QtQuick.Window 2.11

Window {
	id: root
	width: 400; height: 400
	visible: true
	color: "red"
	title: qsTr("Hello World App")
	
	Rectangle {
		id: blue
		anchors.centerIn: parent
		width: root.width / 2; height: root.height / 6
		border.color: "#def"
		border.width: 5
		radius: 20
		gradient: Gradient {
			GradientStop { position: 0.0; color: "lightsteelblue" }
			GradientStop { position: 1.0; color: "blue" }
		}
	}

	Text {
		anchors.centerIn: blue
		text: "Hello <b>World</b>"
		color: "white"
		font.pixelSize: Math.round(blue.height / 3)
		width: blue.width
		wrapMode: Text.WordWrap
	}
	
	MouseArea {
		anchors.fill: parent
		onClicked: {
			Qt.quit();
		}		
	}
}
