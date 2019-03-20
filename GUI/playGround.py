"""
https://pythonspot.com

playground for messing around and testing the PyQT5 library

"""

import sys, os
from PyQt5.QtWidgets import QApplication, QWidget, QTableWidget, QMainWindow, QPushButton, QMessageBox, QAction, \
QTableView, QTableWidgetItem, QVBoxLayout, QSizePolicy, QProgressBar, QLabel, QInputDialog
from PyQt5.QtGui import QIcon, QPixmap, QStatusTipEvent
from PyQt5.QtCore import pyqtSlot, QSize, QTimer
import widget


class App(QMainWindow):
    def __init__(self):
        super().__init__()
        self.title = "Queen's Hyperloop Design Team"
        self.left = 600
        self.top = 200
        self.width = 1800
        self.height = 900
        self.ping = 5
        self.connectionPort = "No connection"
        self.myWidget = widget.App(self.width,self.height, self)




        # Create a menu
        self.mainMenu = self.menuBar()
        self.commandMenu = self.mainMenu.addMenu('Commands')
        self.connectMenu = self.mainMenu.addMenu('Connection')
        self.viewMenu = self.mainMenu.addMenu('View')

        # Create a menu action
        self.exitButton = QAction('Exit', self)
        self.specsButton = QAction('Specs', self)
        self.rateButton = QAction('Update Refresh Rate', self)
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

        self.rateButton.setShortcut('Ctrl+U')
        self.rateButton.setStatusTip('Update the refresh rate of the data')
        self.viewMenu.addAction(self.rateButton)
        self.rateButton.triggered.connect(self.rateUpdate)

        self.emergencyButton.setShortcut('Ctrl+E')
        self.emergencyButton.setStatusTip('Go into an emergency stop')
        self.commandMenu.addAction(self.emergencyButton)
        self.emergencyButton.triggered.connect(self.myWidget.emergency)




        #set our widget as the main box
        self.setCentralWidget(self.myWidget)
        self.show()



        """
        # create pop up button button
        buttonReply = QMessageBox.question(self, 'Connection', "Connection established with the pod", QMessageBox.Ok, QMessageBox.Cancel)
        if buttonReply == QMessageBox.Ok:
            print('Accepted.')
        """

        # make QTimer
        self.qTimer = QTimer()
        # set interval to 1 s
        self.qTimer.setInterval(1000)  # 1000 ms = 1 s
        # start timer
        self.qTimer.start()


    def specs(self):
        print("kk")
        # TODO show any hidden data ? new window

    def rateUpdate(self):
        refreshRate, okPressed = QInputDialog.getInt(self, "Get integer", "RefreshRate:")
        if okPressed:
            self.myWidget.qTimer.setInterval(refreshRate)

if __name__ == '__main__':
    app = QApplication(sys.argv)
    ex = App()
    sys.exit(app.exec_())