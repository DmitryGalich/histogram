import QtQuick 2.12
import QtQuick.Window 2.12
import QtCharts 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.13
import QtQuick.Dialogs 1.2

Window {
    width: 640
    height: 480

    minimumHeight: 480
    minimumWidth: 640

    visible: true
    title: qsTr("Words histogram creator")

    ColumnLayout {
        id: generalWidget

        anchors.fill: parent

        RowLayout {
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.maximumHeight: parent.height * 0.1

            Button {
                Layout.fillHeight: true
                Layout.fillWidth: true

                text: qsTr("Browse...")

                onClicked: filepathWindow.open()
            }
        }

        ColumnLayout {
            Layout.fillHeight: true
            Layout.fillWidth: true

            ChartView {
                Layout.fillHeight: true
                Layout.fillWidth: true

                antialiasing: true

                legend.visible: false
                theme: ChartView.ChartThemeQt

                BarSeries {
                    axisX: BarCategoryAxis {
                        categories: (MainWindowHandler === null) ? [] : MainWindowHandler.wordsList

                        onCategoriesChanged: {

                        }
                    }

                    axisY: ValueAxis {
                        min: 0
                        max: (MainWindowHandler === null) ? 0 : MainWindowHandler.axisYMax
                    }

                    BarSet {
                        values: (MainWindowHandler === null) ? [] : MainWindowHandler.numbersList
                    }
                }
            }
        }

        ColumnLayout {
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.maximumHeight: parent.height * 0.1

            ProgressBar {
                Layout.fillHeight: true
                Layout.fillWidth: true
                visible: (MainWindowHandler
                          === null) ? false : MainWindowHandler.progressBarVisability
                value: (MainWindowHandler === null) ? 0 : MainWindowHandler.progressValue
            }
        }
    }
    FileDialog {
        id: filepathWindow

        folder: shortcuts.home

        onAccepted: {
            MainWindowHandler.processFilepath(fileUrl)
        }
    }
}
