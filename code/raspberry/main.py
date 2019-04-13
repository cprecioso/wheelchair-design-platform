import os  # To access environment variables
import signal  # To catch the Ctrl+C and end the program properly

from dotenv import load_dotenv

import feather
import mega

# The thing ID and access token
load_dotenv()


def setup():
    feather.setup()
    mega.setup()


def loop():
    feather.loop()
    mega.loop()


def close():
    feather.close()
    mega.close()


setup()


while True:
    loop()


def keyboard_interrupt_handler(signal_num, frame):
    """Make sure we close our program properly"""
    print("Exiting...".format(signal_num))
    close()
    exit(0)


# Register our Keyboard handler to exit
signal.signal(signal.SIGINT, keyboard_interrupt_handler)
