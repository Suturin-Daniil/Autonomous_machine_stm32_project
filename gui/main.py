from PyQt5 import QtWidgets, uic
from PyQt5.QtSerialPort import QSerialPort, QSerialPortInfo
from PyQt5.QtCore import QIODevice
from ctypes import sizeof
from struct import unpack
from typing import Literal
from unicodedata import decimal

app = QtWidgets.QApplication([])
ui = uic.loadUi("d.ui")
ui.setWindowTitle("Stm_gui")

serial = QSerialPort()
serial.setBaudRate(115200)
portlist = []
ports = QSerialPortInfo().availablePorts()
for port in ports:
    portlist.append(port.portName())
ui.comL.addItems(portlist)

def onOpen():
    serial.setPortName(ui.comL.currentText())
    serial.open(QIODevice.ReadWrite)

def onClose():
    serial.close()

def onRead():
    rx =serial.read(2) # Ждет 2 байта на вход
    # if len(rx) > 10:
    #     rx = serial.readLine()
    # if rx == b'':
    #     rx = serial.readLine()
    print(rx)
    rx = unpack('h', rx) # Из bytearray преобразует в 10-е число
    print(rx)
    # rx = unpack('h',rx)
    # rxs = (str(rx, 'utf-8'))
    # data = rxs.split(',')
    ui.lcdT.display(rx[0])

def ledControl(val): # Код светодиода 0
    if val == 2: val = 1
    serialSend([0, val])

def serialSend(data):
    txs = ""
    for el in data:
        txs += str(el)
        # txs += ','
    # txs = txs[:-1]
    # txs += ';'
    serial.write(txs.encode())

# def sendText():
#     txs = 


serial.readyRead.connect(onRead)
ui.openB.clicked.connect(onOpen)
ui.closeB.clicked.connect(onClose)

ui.ledC.stateChanged.connect(ledControl)
# ui.servoC.valueChange.connect(servoControl)

# ui.sendB.clicked.connect(sendText)


ui.show()
app.exec()