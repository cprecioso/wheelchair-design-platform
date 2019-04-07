# Code for Raspberry Pi

The Raspberry reads info from the [Arduino Mega](../mega/README.md) and the [Adafruit Feather](../feather/README.md), decides on it, uploads the input and the decision to the [Data-Centric Design Hub](https://dwd.tudelft.nl/manager/), and send it back through the Arduino Mega to its actuators.

It reads from the Mega through a serial port with messages in [`CmdMessenger`](https://github.com/thijse/Arduino-CmdMessenger) format. The message IDs are available in [the Mega's `Messenger.h` file](../mega/src/Messenger.h).

It reads from the Feather connecting to its BLE chip and reading the appropriate characteristic - the ID of which is available in [the Feather's `Configuration.h` file](../feather/src/Configuration.h).

It's important to fill out the [`sample.env` file](./sample.env) with the required values and rename it to `.env`.
