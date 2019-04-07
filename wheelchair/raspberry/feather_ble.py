import os

import pygatt
from dotenv import load_dotenv

from hub import Property, upload

load_dotenv()
BLUETOOTH_DEVICE_MAC = os.environ['BLUETOOTH_DEVICE_MAC']
GATT_CHARACTERISTIC = "DEADBEEF-4455-6677-8899-AABBCCDDEEFF"

bleAdapter = pygatt.GATTToolBackend()
bleAdapter.start()

feather = bleAdapter.connect(
    BLUETOOTH_DEVICE_MAC, address_type=pygatt.BLEAddressType.random)


def handle_heart_rate(handle: int, value_bytes: bytearray):
    value = int.from_bytes(value_bytes,  byteorder="little")
    upload(Property.HeartRate, [value])


feather.subscribe(GATT_CHARACTERISTIC, callback=handle_heart_rate)
