import QtQuick 2.11
import QtQuick.Window 2.11

Window {
	id: root
	width: 400; height: 400
	visible: true
	color: "red"
	title: qsTr("Hello World App")

	Text {
		anchors.centerIn: parent
		text: "Hello World"
		color: "blue"
	}
	
	MouseArea {
		anchors.fill: parent
		onClicked: {
			Qt.quit();
		}		
	}
}
