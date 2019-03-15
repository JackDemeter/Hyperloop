"""
https://pythonspot.com

playground for messing around and testing the PyQT5 library

"""

import sys
from PyQt5.QtWidgets import QApplication, QWidget, QMainWindow, QPushButton, QMessageBox, QAction, QTableWidget, QTableWidgetItem, QVBoxLayout, QSizePolicy, QProgressBar
from PyQt5.QtGui import QIcon, QPixmap
from PyQt5.QtCore import pyqtSlot, QSize

# QMain window used for status bar
# QMessageBox to bring in pop ups




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