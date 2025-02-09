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
		color: "blue"
		gradient: Gradient {
			GradientStop { position: 0.0; color: "lightsteelblue" }
			GradientStop { position: 1.0; color: "slategray" }
		}
	}
	
	MouseArea {
		id: blueRecMouseArea
		hoverEnabled: true
		anchors.fill: blue
		onClicked: {
			console.log("Hello from QML!")
		}
		onEntered: {
			blue.color = "brown"
			blue.rotation = 45
			fooText.rotation = 45
		}
		onExited: {
			blue.color = "blue"
			blue.rotation = 0
			fooText.rotation = 0
		}
	}

	Text {
		id: fooText
		anchors.centerIn: blueRecMouseArea
		text: "Hello <b>World</b>"
		color: "white"
		font.pixelSize: Math.round(blue.height / 3)
		wrapMode: Text.WordWrap
	}
}
