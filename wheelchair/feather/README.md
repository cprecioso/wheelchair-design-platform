# Code for Adafruit Feather

> This code is managed through [platform-io](https://platformio.org)

The Adafruit Feather handles input from the heart beat sensor.

It simply reads from the sensor every 500ms and uses the Bluetooth LE chip to send its value every 1000ms. You can find the service and characteristic IDs in [`Configuration.h`](src/Configuration.h).
