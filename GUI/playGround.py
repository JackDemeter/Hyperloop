"""
https://pythonspot.com

playground for messing around and testing the PyQT5 library

"""

import sys
from PyQt5.QtWidgets import QApplication, QWidget, QMainWindow, QPushButton, QMessageBox, QAction, QTableWidget, QTableWidgetItem, QVBoxLayout, QSizePolicy, QProgressBar, QLayout, QGridLayout, QDockWidget
from PyQt5.QtGui import QIcon, QPixmap
from PyQt5.QtCore import pyqtSlot, QSize

# QMain window used for status bar
# QMessageBox to bring in pop ups

class WidgetTable(QDockWidget):
    def __init__(self, left = 0, top = 0, width = 100, height = 100):
        super().__init__()
        self.title = 'PyQt5 table - pythonspot.com'
        self.left = left
        self.top = top
        self.width = width
        self.height = height
        self.initUI()

    def initUI(self):
        self.setWindowTitle(self.title)
        self.setGeometry(self.left, self.top, self.width, self.height)

        self.createTable()

        # Add box layout, add table to box layout and add box layout to widget
        self.layout = QVBoxLayout()
        self.layout.addWidget(self.tableWidget)
        self.setLayout(self.layout)

        # Show widget
        self.show()

    def createTable(self):
        # Create table
        self.tableWidget = QTableWidget()
        self.tableWidget.setRowCount(4)
        self.tableWidget.setColumnCount(2)
        self.tableWidget.setItem(0, 0, QTableWidgetItem("Cell (1,1)"))
        self.tableWidget.setItem(0, 1, QTableWidgetItem("Cell (1,2)"))
        self.tableWidget.setItem(1, 0, QTableWidgetItem("Cell (2,1)"))
        self.tableWidget.setItem(1, 1, QTableWidgetItem("Cell (2,2)"))
        self.tableWidget.setItem(2, 0, QTableWidgetItem("Cell (3,1)"))
        self.tableWidget.setItem(2, 1, QTableWidgetItem("Cell (3,2)"))
        self.tableWidget.setItem(3, 0, QTableWidgetItem("Cell (4,1)"))
        self.tableWidget.setItem(3, 1, QTableWidgetItem("Cell (4,2)"))
        self.tableWidget.move(0, 0)

        # table selection change
        self.tableWidget.doubleClicked.connect(self.on_click)

    @pyqtSlot()
    def on_click(self):
        print("\n")
        for currentQTableWidgetItem in self.tableWidget.selectedItems():
            print(currentQTableWidgetItem.row(), currentQTableWidgetItem.column(), currentQTableWidgetItem.text())


class App(QMainWindow):
    def __init__(self):
        super().__init__()
        self.title = "Queen's Hyperloop Design Team"
        self.left = 600
        self.top = 200
        self.width = 1280
        self.height = 720
        self.windowIcon()
        self.ping = 5
        self.connectionPort = "No connection"
        self.initUI()

    def initUI(self):

        self.setWindowTitle(self.title)
        self.setGeometry(self.left, self.top, self.width, self.height)
        self.setWindowIcon(QIcon(r'images\QH_icon.png'))

        # self.addDockWidget()
        # add widget table
        table = WidgetTable(100, 100,200,200)
        self.setCentralWidget(table)

        # create a button
        button = QPushButton('Emergency\nStop', self)
        button.setStyleSheet("color:black")
        button.setToolTip('This button engages the pods fault state')
        button.move(1080, 30)
        # colour/style button
        button.setStyleSheet("background-color:rgb(230,80,80); color:black; font-size:25px")
        button.resize(200,70)
        # link button to pyqtslot
        button.clicked.connect(self.on_click)

        # Create a menu
        mainMenu = self.menuBar()
        fileMenu = mainMenu.addMenu('File')
        editMenu = mainMenu.addMenu('Edit')
        viewMenu = mainMenu.addMenu('View')
        # Extra menu settings
        exitButton = QAction(QIcon(r'images\QH_icon.png'), 'Exit', self)
        exitButton.setShortcut('Ctrl+Q')
        exitButton.setStatusTip('Exit application')
        exitButton.triggered.connect(self.close)
        fileMenu.addAction(exitButton)
        # Create a status bar at the bottom of the page
        self.statusBar().showMessage('Ping: %dms              Port: %s              Other: %s' %(self.ping, self.connectionPort,"None"))

        # create a progress bar
        progress = QProgressBar(self)
        progress.setGeometry(450, 150, 800, 15)
        progress.setValue(50)





        self.show()

        # create pop up button button
        buttonReply = QMessageBox.question(self, 'Connection', "Connection established with the pod", QMessageBox.Ok, QMessageBox.Cancel)
        if buttonReply == QMessageBox.Ok:
            print('Accepted.')


    # creates a slot for the button
    @pyqtSlot()
    def on_click(self):
        print('Fault State Engaged')
        # TODO engage the fault state on pod


if __name__ == '__main__':
    app = QApplication(sys.argv)
    ex = App()
    sys.exit(app.exec_())