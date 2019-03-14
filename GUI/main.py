"""
https://pythonspot.com

playground for messing around and testing the PyQT5 library

"""

import sys
from PyQt5.QtWidgets import QApplication, QWidget, QMainWindow, QPushButton, QMessageBox, QAction, QTableWidget, QTableWidgetItem, QVBoxLayout
from PyQt5.QtGui import QIcon
from PyQt5.QtCore import pyqtSlot

# QMain window used for status bar
# QMessageBox to bring in pop ups




class App(QMainWindow):
    def __init__(self):
        super().__init__()
        self.title = "Queen's Hyperloop Design Team"
        self.left = 1200
        self.top = 200
        self.width = 640
        self.height = 480
        self.windowIcon()
        self.ping = 5
        self.initUI()

    def initUI(self):

        self.setWindowTitle(self.title)
        self.setGeometry(self.left, self.top, self.width, self.height)
        self.setWindowIcon(QIcon(r'images\QH_icon.png'))
        # self.addDockWidget()

        # create a button
        button = QPushButton('PyQt5 button', self)
        button.setToolTip('This is an example button')
        button.move(300, 70)
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
        self.statusBar().showMessage('Ping: %sms' %(self.ping))

        self.show()





        # create pop up button button
        buttonReply = QMessageBox.question(self, 'Connection', "Connection established with the pod", QMessageBox.Ok, QMessageBox.Cancel)
        if buttonReply == QMessageBox.Ok:
            print('Accepted.')


    # creates a slot for the button
    @pyqtSlot()
    def on_click(self):
        print('PyQt5 button click')


if __name__ == '__main__':
    app = QApplication(sys.argv)
    ex = App()
    sys.exit(app.exec_())