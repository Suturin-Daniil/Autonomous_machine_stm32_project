from PyQt5 import QtWidgets, uic
from PyQt5.QtSerialPort import QSerialPort, QSerialPortInfo
from PyQt5.QtCore import QIODevice
from ctypes import sizeof
from struct import pack, unpack
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

def servoWrite(): # код серво 1
    val = int(ui.servoSlider.value())
    serialSend([1, val])

def serialSend(data):
    if data[0] == 0:
        if data[1] == 1:
        # led_int_to_bytes = pack('i', data[1])
        # check_byte = pack('h', 0)
        # print(check_byte[0], check_byte[1], led_int_to_bytes[0], led_int_to_bytes[1], led_int_to_bytes[2], led_int_to_bytes[3])
        # led_list_bytes = [check_byte[0], check_byte[1], led_int_to_bytes[0], led_int_to_bytes[1], led_int_to_bytes[2], led_int_to_bytes[3]]
        # led_bytearray = bytearray(led_list_bytes)
        # print(led_bytearray)
            serial.write(bytearray(b'\x00\x00\x01\x00\x00\x00'))
        if data[1] == 0:
            serial.write(bytearray(b'\x00\x00\x00\x00\x00\x00'))
    if data[0] == 1:
        servo_int_to_bytes = pack('i', data[1])
        check_byte = pack('h', 1)
        servo_list_bytes = [check_byte[0], check_byte[1], servo_int_to_bytes[0], servo_int_to_bytes[1], servo_int_to_bytes[2], servo_int_to_bytes[3]]
        servo_bytearray = bytearray(servo_list_bytes)
        serial.write(servo_bytearray)
        
    

serial.readyRead.connect(onRead)
ui.openB.clicked.connect(onOpen)
ui.closeB.clicked.connect(onClose)

ui.ledC.stateChanged.connect(ledControl)
ui.servoSlider.valueChanged.connect(servoWrite)



ui.show()
app.exec()