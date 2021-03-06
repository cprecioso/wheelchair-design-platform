import os
import signal
from random import randint

import output
from hub import Property, upload
from internal_serial import SEMICOLON, Message, serial


def setup():
    None


def loop():
    # Read one line
    raw_line_bytes: bytes = serial.read_until(SEMICOLON)
    line_bytes: bytes = raw_line_bytes.strip().strip(SEMICOLON)

    # If the line is not empty
    if len(line_bytes) > 0:
        # Convert the bytes into string
        line = line_bytes.decode('utf-8')
        # Split the string using commas as separator, we get a list of strings
        args = line.split(',')

        messageId = int(args.pop(0))

        if messageId == Message.kStatus:
            print("Status:", args[0])
            upload(Property.Status, args[0])
        elif messageId == Message.kGPS:
            lat = float(args[0])
            lon = float(args[1])
            upload(Property.Location, [lat, lon])
            direction = output.Direction(randint(0, 3))
            output.show_direction(direction)
        elif messageId == Message.kCalibration:
            sys = int(args[0])
            gyro = int(args[1])
            mag = int(args[2])
            accel = int(args[3])
            upload(Property.Calibration, [sys, gyro, mag, accel])
        elif messageId == Message.kOrientation:
            x = float(args[0])
            y = float(args[1])
            z = float(args[2])
            upload(Property.Orientation, [x, y, z])
            output.show_direction(x)
        else:
            print("unknown!", messageId, args)


def close():
    serial.close()
