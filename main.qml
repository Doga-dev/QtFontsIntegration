import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Layouts 1.3

Window {
	id: window
	visible: true
	width: 640
	height: 480
	title: qsTr("Test Fonts integration")

	ColumnLayout {
		id: column
		height: 120
		anchors.right: parent.right
  anchors.left: parent.left
  anchors.top: parent.top

		Text {
			id: title
			width: parent.width
			text: "Hello World"
			font.family: "Android"
			font.pixelSize: 36
			fontSizeMode: Text.Fit
			Layout.alignment: Qt.AlignHCenter
		}
		Text {
			id: oldFont
			width: parent.width
			text: "Original default font: " + defAppFont
			font.family: "Exo"
			font.pixelSize: 24
			fontSizeMode: Text.Fit
			Layout.alignment: Qt.AlignHCenter
		}
		Text {
			id: newFont
			width: parent.width
			text: "New default font: " + newAppFont
			font.family: "Generica"
			font.pixelSize: 24
			fontSizeMode: Text.Fit
			Layout.alignment: Qt.AlignHCenter
		}
	}

	ListView {
		anchors.bottom: parent.bottom
		anchors.top: column.bottom
		anchors.right: parent.right
		anchors.left: parent.left
		model: Qt.fontFamilies()
		Layout.alignment: Qt.AlignHCenter
		clip: true

		delegate: Item {
			height: 40;
			width: ListView.view.width
			Text {
				anchors.centerIn: parent
				text: modelData;
				font.family: modelData;
				//font.family: "Monoglyceride"
			}
		}
	}
}

/*##^##
Designer {
	D{i:5;anchors_height:380;anchors_width:640;anchors_x:0;anchors_y:114}
}
##^##*/
