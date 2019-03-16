import sys
from PyQt5.QtWidgets import QApplication, QWidget, QMenuBar, QStatusBar, QPushButton, QMessageBox, QAction, QTableView, QTableWidget, QTableWidgetItem, QVBoxLayout, QSizePolicy, QProgressBar, QLabel, QVBoxLayout, QHBoxLayout, QLayout, QGridLayout, QComm
from PyQt5.QtGui import QIcon, QPixmap
from PyQt5.QtCore import pyqtSlot, QSize

class App(QWidget):
    def __init__(self, width, height, mainWindow):
        super().__init__()
        self.title = "Queen's Hyperloop Design Team"
        self.left = 600
        self.top = 200
        self.width = width
        self.height = height
        self.ping = 5
        self.connectionPort = "No connection"
        self.status = "RTL"
        self.mainWindow = mainWindow

        self.tableWidget = QTableWidget(4, 2)
        # self.layout = QVBoxLayout(self)
        self.layout = QGridLayout(self)
        # calls GUI
        self.initUI()

    def initUI(self):
        self.setWindowTitle(self.title)
        self.setFixedSize(1280, 680)

        # add images
        self.titleLogo = QLabel()
        pixmap = QPixmap(r'images\QH_logo.png')
        pixmap = pixmap.scaled(400, 100)
        self.titleLogo.setPixmap(pixmap)
        self.titleLogo.resize(300,200)
        self.layout.addWidget(self.titleLogo,0,0)

        self.sample = QLabel()
        pixmap = QPixmap(r'images\example.png')
        pixmap = pixmap.scaled(500, 600)
        self.sample.setPixmap(pixmap)
        self.sample.resize(500, 400)
        self.layout.addWidget(self.sample,1,1)


        # adds table widget
        self.tableWidget.setItem(0, 0, QTableWidgetItem("Cell (1,1)"))
        self.tableWidget.setItem(0, 1, QTableWidgetItem("Cell (1,2)"))
        self.tableWidget.setItem(1, 0, QTableWidgetItem("Cell (2,1)"))
        self.tableWidget.setItem(1, 1, QTableWidgetItem("Cell (2,2)"))
        self.tableWidget.setItem(2, 0, QTableWidgetItem("Cell (3,1)"))
        self.tableWidget.setItem(2, 1, QTableWidgetItem("Cell (3,2)"))
        self.tableWidget.setItem(3, 0, QTableWidgetItem("Cell (4,1)"))
        self.tableWidget.setItem(3, 1, QTableWidgetItem("Cell (4,2)"))
        self.tableWidget.setFixedSize(217,400)
        self.layout.addWidget(self.tableWidget,1,0)




        # add label for state
        self.Statelabel = QLabel("State: {}".format(self.status), self)
        self.Statelabel.move(800, 00)
        self.Statelabel.setStyleSheet("color:black; font-size:40px")
        self.Statelabel.resize(250, 70)
        # create a button
        button = QPushButton('Emergency\nStop', self)
        button.setStyleSheet("color:black")
        button.setToolTip('This button engages the pods fault state')
        button.move(1080, 0)
        # colour/style button
        button.setStyleSheet("background-color:rgb(230,80,80); color:black; font-size:25px")
        button.resize(200,70)
        # link button to pyqtslot
        button.clicked.connect(self.mainWindow.emergency)

        # create a progress bar
        progress = QProgressBar(self)
        progress.setGeometry(450, 100, 800, 10)
        progress.setValue(50)




    # creates a slot for the button
    @pyqtSlot()
    def on_click(self):
        print('Fault State Engaged')
        # TODO engage the fault state on pod
