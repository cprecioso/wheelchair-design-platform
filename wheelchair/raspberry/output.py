from enum import IntEnum

from internal_serial import Message, sendCommand


def show_heart_rate(rate: int):
    r = g = b = 0
    if rate < 550:
        g = 128
    elif rate < 800:
        r = 253
        g = 106
        b = 2
    else:
        r = 250

    sendCommand([Message.kInnerLight.value, r, g, b])


class Direction(IntEnum):
    Left = 0
    Back = 1
    Right = 2
    Forward = 3


def show_direction(direction: Direction):
    sendCommand([Message.kOuterLight.value, direction])


def show_orientation(orientation: int):
    sendCommand([Message.kServo.value, 180 - orientation])
