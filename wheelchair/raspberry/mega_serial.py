import os
from enum import IntEnum

from serial import Serial

# Start reading the serial port
serial = Serial(
    port=os.environ['SERIAL'],
    baudrate=115200,
    timeout=2)

SEMICOLON = ";".encode("ascii")

Message = IntEnum(
    "Message", "kAcknowledge kError kStatus kGPS kOrientation kCalibration kServo kInnerLight kOuterLight", start=0)
