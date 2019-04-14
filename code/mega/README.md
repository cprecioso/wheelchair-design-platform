# Code for Arduino Mega

> This code is managed through [platform-io](https://platformio.org)

The Arduino Mega handles input from the GPS and Orientation sensors, and at the same time manages the output to the Servo and the two LED rings.

It has not decision-making and instead relies on the information sent and received through Serial protocol connected to the Raspberry with USB. It uses [`CmdMessenger`](https://github.com/thijse/Arduino-CmdMessenger)'s protocol:

    [message id],[arg 1],[arg 2],...,[arg n];

The message codes are available at [`Messenger.h`](./src/Messenger.h), and the code responsible for every peripheral is in a differente file, with the [`main.cpp`](./src/main.cpp) file calling each as needed. We use C++ namespaces to organize code to split it between different files.
