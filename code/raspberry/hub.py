import os
from enum import Enum

from dcd.entities.property import PropertyType
from dcd.entities.thing import Thing
from dotenv import load_dotenv

load_dotenv()

# The thing ID and access token
THING_ID = os.environ['THING_ID']
THING_TOKEN = os.environ['THING_TOKEN']


# Instantiate a thing with its credential
db = Thing(thing_id=THING_ID, token=THING_TOKEN)

# We can read the details of our thing,
# i.e. retrieving its information from the hub
db.read()

# Copied from the DCD hub


class Property(Enum):
    Location = "location-512c"
    Calibration = "calibration-da32"
    Status = "status-4a4f"
    Orientation = "orientation-016a"
    HeartRate = "heart-rate-7d9c"


def upload(name: Property, values: list):
    # Get the property from the thing
    prop = db.properties[name.value]
    # If we find the property, we update the values (rest of the list)
    if prop is not None:
        prop.update_values(values)
    # Otherwise, we show a warning
    else:
        print('Warning: unknown property ' + name)
