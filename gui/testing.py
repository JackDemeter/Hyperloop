import sys
from PyQt5.QtWidgets import QApplication, QMainWindow, QLabel
from PyQt5.QtCore import QTimer

class MainWindow(QMainWindow):
  # constructor
  def __init__(self):
    super().__init__()
    # counter
    self.i = 0
    # add QLabel
    self.qLbl = QLabel('Not yet initialized')
    self.setCentralWidget(self.qLbl)
    # make QTimer
    self.qTimer = QTimer()
    # set interval to 1 s
    self.qTimer.setInterval(1000) # 1000 ms = 1 s
    # connect timeout signal to signal handler
    self.qTimer.timeout.connect(self.getSensorValue)
    # start timer
    self.qTimer.start()

  def getSensorValue(self):
    self.i += 1
    # print('%d. call of getSensorValue()' % self.i)
    self.qLbl.setText('%d. call of getSensorValue()' % self.i)

qApp = QApplication(sys.argv)
# setup GUI
qWin = MainWindow()
qWin.show()
# run application
sys.exit(qApp.exec_())