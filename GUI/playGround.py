"""
https://pythonspot.com

playground for messing around and testing the PyQT5 library

"""

import sys, os
from PyQt5.QtWidgets import QApplication, QWidget, QTableWidget, QMainWindow, QPushButton, QMessageBox, QAction, QTableView, QTableWidgetItem, QVBoxLayout, QSizePolicy, QProgressBar, QLabel
from PyQt5.QtGui import QIcon, QPixmap, QStatusTipEvent
from PyQt5.QtCore import pyqtSlot, QSize
import widget


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
        self.status = "please"

        # Create a menu
        self.mainMenu = self.menuBar()
        self.commandMenu = self.mainMenu.addMenu('Commands')
        self.connectMenu = self.mainMenu.addMenu('Connection')
        self.viewMenu = self.mainMenu.addMenu('View')

        # Create a menu action
        self.exitButton = QAction('Exit', self)
        self.specsButton = QAction('Specs', self)
        self.emergencyButton = QAction('Emergency Stop', self)

        # calls GUI
        self.initUI()

    def initUI(self):
        self.setWindowTitle(self.title)
        self.setFixedSize(self.width, self.height)
        self.setWindowIcon(QIcon(os.getcwd() + r'\images\QH_icon.png'))

        # Create a status bar at the bottom of the page
        self.statusBar().showMessage('Ping: %dms              Port: %s              Other: %s' % (self.ping, self.connectionPort, "None"))
        # TODO create a slot that constantly refreshes this

        # Extra menu settings
        self.exitButton.setShortcut('Ctrl+Q')
        self.exitButton.setStatusTip('Exit application')
        self.commandMenu.addAction(self.exitButton)
        self.exitButton.triggered.connect(self.close)

        self.specsButton.setShortcut('Ctrl+V')
        self.specsButton.setStatusTip('Look at the harder specs')
        self.viewMenu.addAction(self.specsButton)
        self.specsButton.triggered.connect(self.specs)

        self.emergencyButton.setShortcut('Ctrl+E')
        self.emergencyButton.setStatusTip('Go into an emergency stop')
        self.commandMenu.addAction(self.emergencyButton)
        self.emergencyButton.triggered.connect(self.emergency)


        #set our widget as the main box
        self.setCentralWidget(widget.App(1280,720, self))
        self.show()

        """
        # create pop up button button
        buttonReply = QMessageBox.question(self, 'Connection', "Connection established with the pod", QMessageBox.Ok, QMessageBox.Cancel)
        if buttonReply == QMessageBox.Ok:
            print('Accepted.')
        """

    def specs(self):
        print("kk")
        # TODO show any hidden data ? new window?


    # creates a slot for the button
    @pyqtSlot()
    def emergency(self):
        print('Fault State Engaged')
        self.status = "FAULT"
        # TODO engage the fault state on pod


if __name__ == '__main__':
    app = QApplication(sys.argv)
    ex = App()
    sys.exit(app.exec_())