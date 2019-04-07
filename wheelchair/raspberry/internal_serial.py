import os
from enum import IntEnum

from serial import Serial

# Start reading the serial port
serial = Serial(
    port=os.environ['SERIAL'],
    baudrate=115200,
    timeout=2)

SEMICOLON = ";".encode("ascii")


class Message(IntEnum):
    kAcknowledge = 0
    kError = 1
    kStatus = 2
    kGPS = 3
    kOrientation = 4
    kCalibration = 5
    kServo = 6
    kInnerLight = 7
    kOuterLight = 8

