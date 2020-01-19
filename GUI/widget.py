import sys
from PyQt5.QtWidgets import QApplication, QWidget, QMenuBar, QStatusBar, QPushButton, QMessageBox, QAction, QTableView, \
    QTableWidget, QTableWidgetItem, QVBoxLayout, QSizePolicy, QProgressBar, QLabel, QVBoxLayout, QHBoxLayout, \
    QLayout, QGridLayout, QInputDialog, QGroupBox
from PyQt5.QtGui import QIcon, QPixmap,QColor
from PyQt5.QtCore import pyqtSlot, QTimer
import UDPsending

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
        self.stateInteger = 1
        self.mainWindow = mainWindow

        # make QTimer
        self.qTimer = QTimer()

        # make table widget
        self.tableWidget = QTableWidget(8, 4)
        self.tableWidget.horizontalHeader().setVisible(False)
        self.tableWidget.verticalHeader().setVisible(False)

        # layout
        self.layout = QVBoxLayout(self)         # Main Layout
        self.sublayout = QHBoxLayout(self)      # Sub-Layout for the picture and the table
        self.buttonlayout = QHBoxLayout(self)   # Sub-Layout for the buttons

        self.layout.addStretch()

        self.sublayout.addStretch(1)
        self.sublayout.setSpacing(150)

        # groupbox
        
        self.tableBox = QGroupBox()
        self.tableBox.setLayout(self.sublayout)
        self.layout.addWidget(self.tableBox)

        self.buttonBox = QGroupBox()
        self.buttonBox.setLayout(self.buttonlayout)
        self.layout.addWidget(self.buttonBox)

        # calls GUI
        self.launchString = "Ready to Launch"
        self.isLaunch = False
        self.Statelabel = QLabel(self)
        self.mountbutton = QPushButton("Mount", self)

        # LOGO
        self.titleLogo = QLabel(self)
        pixmap = QPixmap(r'images\QH_logo.png')
        pixmap = pixmap.scaled(251, 51)
        self.titleLogo.setPixmap(pixmap)
        self.titleLogo.resize(300, 400)
        self.titleLogo.move(25, -150)

        self.initUI()

    def initUI(self):
        self.setWindowTitle(self.title)
        self.setGeometry(100, 100, self.width, self.height)

        self.sample = QLabel()
        pixmap = QPixmap(r'images\pod.png')
        pixmap = pixmap.scaled(750, 394)
        self.sample.setPixmap(pixmap)
        self.sample.setFixedSize(750, 394)
        self.sublayout.addWidget(self.sample)
        #self.sublayout.addStretch(1)
        self.sublayout.setSpacing(100)

        # TABLE

        self.tableWidget.setItem(0, 0, QTableWidgetItem(""))
        self.tableWidget.setItem(0, 1, QTableWidgetItem("Min"))
        self.tableWidget.setItem(0, 2, QTableWidgetItem("Value"))
        self.tableWidget.setItem(0, 3, QTableWidgetItem("Max"))
        self.tableWidget.item(0,0).setBackground(QColor(0,0,0))

        self.tableWidget.setItem(1, 0, QTableWidgetItem("Battery Temperature"))
        self.tableWidget.setItem(1, 1, QTableWidgetItem("0"))
        self.tableWidget.setItem(1, 2, QTableWidgetItem("Cell (1,2)"))
        self.tableWidget.setItem(1, 3, QTableWidgetItem("60"))
        self.tableWidget.item(1,2).setBackground(QColor(0,255,0))
        
        self.tableWidget.setItem(2, 0, QTableWidgetItem("Motor Temperature"))
        self.tableWidget.setItem(2, 1, QTableWidgetItem("-20"))
        self.tableWidget.setItem(2, 2, QTableWidgetItem(str(0)))
        self.tableWidget.setItem(2, 3, QTableWidgetItem("180"))
        self.tableWidget.item(2,2).setBackground(QColor(255,0,0))

        self.tableWidget.setItem(3, 0, QTableWidgetItem("Pod Temperature"))
        self.tableWidget.setItem(3, 1, QTableWidgetItem("-20"))
        self.tableWidget.setItem(3, 2, QTableWidgetItem(str(0)))
        self.tableWidget.setItem(3, 3, QTableWidgetItem("60"))
        self.tableWidget.item(3,2).setBackground(QColor(255,0,0))        

        self.tableWidget.setItem(4, 0, QTableWidgetItem("Battery Voltage (Motor)"))
        self.tableWidget.setItem(4, 1, QTableWidgetItem("40"))
        self.tableWidget.setItem(4, 2, QTableWidgetItem(str(0)))
        self.tableWidget.setItem(4, 3, QTableWidgetItem("55"))
        self.tableWidget.item(4,2).setBackground(QColor(255,0,0))

        self.tableWidget.setItem(5, 0, QTableWidgetItem("Battery Voltage (Electronics)"))
        self.tableWidget.setItem(5, 1, QTableWidgetItem("20"))
        self.tableWidget.setItem(5, 2, QTableWidgetItem(str(0)))
        self.tableWidget.setItem(5, 3, QTableWidgetItem("27.5"))
        self.tableWidget.item(5,2).setBackground(QColor(255,0,0))

        self.tableWidget.setItem(6, 0, QTableWidgetItem("Pressure Vessel Pressure"))
        self.tableWidget.setItem(6, 1, QTableWidgetItem("10"))
        self.tableWidget.setItem(6, 2, QTableWidgetItem(str(0)))
        self.tableWidget.setItem(6, 3, QTableWidgetItem("20"))
        self.tableWidget.item(6,2).setBackground(QColor(255,0,0))

        self.tableWidget.setItem(7, 0, QTableWidgetItem("Break Air Tank Pressure"))
        self.tableWidget.setItem(7, 1, QTableWidgetItem("85")) 
        self.tableWidget.setItem(7, 2, QTableWidgetItem(str(0)))
        self.tableWidget.setItem(7, 3, QTableWidgetItem("109"))
        self.tableWidget.item(7,2).setBackground(QColor(255,0,0))


        self.tableWidget.setColumnWidth(0,200)
        self.tableWidget.setFixedSize(800,500)
        self.sublayout.addWidget(self.tableWidget)
        self.sublayout.addStretch(0)
        self.sublayout.addSpacing(50)
        #self.layout.addLayout(self.sublayout)



        # STATE LABEL

        self.Statelabel.setText("State: {}".format(self.state))
        self.Statelabel.move(800, -10)
        self.Statelabel.setStyleSheet("color:black; font-size:40px")
        self.Statelabel.resize(450, 70)

        #EMERGENCY STOP BUTTON

        self.Emergbutton = QPushButton('Emergency\nStop', self)
        self.Emergbutton.setStyleSheet("color:black")
        self.Emergbutton.setToolTip('This button engages the pods fault state')
        #self.Emergbutton.move(self.width - 200, 0)
        self.buttonlayout.addWidget(self.Emergbutton)
        # colour/style button
        self.Emergbutton.setStyleSheet("background-color:rgb(230,80,80); color:black; font-size:25px")
        self.Emergbutton.setFixedSize(200,70)
        # link button to pyqtslot
        self.Emergbutton.clicked.connect(self.emergency)

        #READY TO LAUNCH BUTTON
        self.Launchbutton = QPushButton(self.launchString, self)
        self.Launchbutton.setStyleSheet("color:black")
        self.Launchbutton.setToolTip('This button engages the pods fault state')
        #self.Launchbutton.move(self.width - 175, 140)
        self.buttonlayout.addWidget(self.Launchbutton)
        # colour/style button
        self.Launchbutton.setStyleSheet("background-color:rgb(200,200,200); color:black; font-size:16px")
        self.Launchbutton.setFixedSize(150, 40)
        # link button to pyqtslot
        self.Launchbutton.clicked.connect(self.launch)

        # todo make this a function call
        if self.isLaunch != True:
            #SAFE TO APPROACH BUTTON
            self.mountbutton.setText("Safe to Approach")
            self.mountbutton.setToolTip('This button sets the pod into a mounting state')
            # self.mountbutton.move(self.width - 175, 70)
            self.buttonlayout.addWidget(self.mountbutton)
            # colour/style button
            self.mountbutton.setStyleSheet("background-color:rgb(200,200,200); color:black; font-size:16px")
            self.mountbutton.setFixedSize(150, 40)
            # link button to pyqtslot
            self.mountbutton.clicked.connect(self.mount)

        
        #self.layout.addLayout(self.buttonlayout)
        self.layout.addStretch()
        self.layout.addSpacing(0)

        # PROGRESS BAR
        progress = QProgressBar(self)
        progress.setGeometry(600, 65, 800, 25)
        progress.setValue(50)

        # set interval to 1 s
        self.qTimer.setInterval(20)  # 1000 ms = 1 s
        # connect timeout signal to signal handler
        self.qTimer.timeout.connect(self.update)
        # start timer
        self.qTimer.start()

    @pyqtSlot()
    def update(self):
        # self.status = getStatus()
        self.Statelabel.setText("Status: %s" %(self.state))
        UDPsending.send_via_udp(self.stateInteger)
        # TODO: ADD BLOCK FOR UDP READ AND THEN UPDATE GUI VALUES

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
            self.stateInteger = 1
    # creates a slot for the button
    @pyqtSlot()
    def emergency(self):
        print('Fault State Engaged')
        self.state = "Fault"
        self.stateInteger = 0
        # TODO engage the fault state on pod

    # creates a slot for the button
    @pyqtSlot()
    def readyLaunch(self):
        print('Prepared for launch engaged')
        self.state = "Ready to Launch"
        self.stateInteger = 1
        self.launch = True
        # TODO engage launch of pod

    # creates a slot for the button
    @pyqtSlot()
    def launch(self):
        print('Launch engaged')
        self.state = "Launch"
        self.stateInteger = 2
        self.launch = True
        # TODO engage launch of pod

    # creates a slot for the button
    @pyqtSlot()
    def on_click(self):
        print('Fault State Engaged')
        # TODO engage the fault state on pod

