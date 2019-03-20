import sys
from PyQt5.QtWidgets import QApplication, QWidget, QMenuBar, QStatusBar, QPushButton, QMessageBox, QAction, QTableView, \
    QTableWidget, QTableWidgetItem, QVBoxLayout, QSizePolicy, QProgressBar, QLabel, QVBoxLayout, QHBoxLayout, \
    QLayout, QGridLayout, QInputDialog
from PyQt5.QtGui import QIcon, QPixmap
from PyQt5.QtCore import pyqtSlot, QTimer

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
        self.state = "No Connection"
        self.mainWindow = mainWindow

        # make QTimer
        self.qTimer = QTimer()

        self.tableWidget = QTableWidget(4, 2)
        # self.layout = QVBoxLayout(self)
        self.layout = QGridLayout(self)
        # calls GUI
        self.launchString = "Ready to Launch"
        self.isLaunch = False

        self.Statelabel = QLabel(self)
        self.mountbutton = QPushButton("Mount", self)

        # add images
        self.titleLogo = QLabel()
        pixmap = QPixmap(r'images\QH_logo.png')
        pixmap = pixmap.scaled(400, 100)
        self.titleLogo.setPixmap(pixmap)
        self.titleLogo.resize(300, 200)
        self.layout.addWidget(self.titleLogo, 0, 0)

        self.initUI()

    def initUI(self):
        self.setWindowTitle(self.title)
        self.setFixedSize(self.width, self.height)



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
        self.tableWidget.setFixedSize(330,500)
        self.layout.addWidget(self.tableWidget,1,0)




        # add label for state

        self.Statelabel.setText("State: {}".format(self.state))
        self.Statelabel.move(800, 00)
        self.Statelabel.setStyleSheet("color:black; font-size:40px")
        self.Statelabel.resize(450, 70)

        # create a button
        self.Emergbutton = QPushButton('Emergency\nStop', self)
        self.Emergbutton.setStyleSheet("color:black")
        self.Emergbutton.setToolTip('This button engages the pods fault state')
        self.Emergbutton.move(self.width - 200, 0)
        # colour/style button
        self.Emergbutton.setStyleSheet("background-color:rgb(230,80,80); color:black; font-size:25px")
        self.Emergbutton.resize(200,70)
        # link button to pyqtslot
        self.Emergbutton.clicked.connect(self.emergency)

        # create a button
        self.Launchbutton = QPushButton(self.launchString, self)
        self.Launchbutton.setStyleSheet("color:black")
        self.Launchbutton.setToolTip('This button engages the pods fault state')
        self.Launchbutton.move(self.width - 175, 140)
        # colour/style button
        self.Launchbutton.setStyleSheet("background-color:rgb(200,200,200); color:black; font-size:16px")
        self.Launchbutton.resize(150, 40)
        # link button to pyqtslot
        self.Launchbutton.clicked.connect(self.launch)

        # todo make this a function call
        if self.isLaunch != True:
            # create a button
            self.mountbutton.setText("Safe to Approach")
            self.mountbutton.setToolTip('This button sets the pod into a mounting state')
            self.mountbutton.move(self.width - 175, 70)
            # colour/style button
            self.mountbutton.setStyleSheet("background-color:rgb(200,200,200); color:black; font-size:16px")
            self.mountbutton.resize(150, 40)
            # link button to pyqtslot
            self.mountbutton.clicked.connect(self.mount)


        # create a progress bar
        progress = QProgressBar(self)
        progress.setGeometry(450, 100, 800, 10)
        progress.setValue(50)

        # set interval to 1 s
        self.qTimer.setInterval(1000)  # 1000 ms = 1 s
        # connect timeout signal to signal handler
        self.qTimer.timeout.connect(self.update)
        # start timer
        self.qTimer.start()

    @pyqtSlot()
    def update(self):
        # TODO update data
        # TODO create a get data function (TALK TO JAKE)
        # self.status = getStatus()
        self.Statelabel.setText("Status: %s" %(self.state))

    # creates a slot for the button
    @pyqtSlot()
    def mount(self):
        print('Mounting process has been started')
        self.state = "Mount"
        # create pop up button button
        buttonReply = QMessageBox.question(self, 'Mounting', "The pod is currenly in the mounting state, press OK once the pod is in the proper position.", QMessageBox.Ok,
                                           QMessageBox.Cancel)
        if buttonReply == QMessageBox.Ok:
            # TODO reengage the brakes
            print('Mounting complete')
            self.Statelabel.setText("State: Safe to Approach")


    # creates a slot for the button
    @pyqtSlot()
    def emergency(self):
        print('Fault State Engaged')
        self.state = "Fault"
        # TODO engage the fault state on pod

    # creates a slot for the button
    @pyqtSlot()
    def readyLaunch(self):
        print('Prepared for launch engaged')
        self.state = "Ready to Launch"
        self.launch = True
        # TODO engage launch of pod

    # creates a slot for the button
    @pyqtSlot()
    def launch(self):
        print('Launch engaged')
        self.state = "Launch"
        self.launch = True
        # TODO engage launch of pod


    # creates a slot for the button
    @pyqtSlot()
    def on_click(self):
        print('Fault State Engaged')
        # TODO engage the fault state on pod
