# Logic

> The logic described here resides mainly in the [`output.py` file](../code/raspberry/output.py) of the Raspberry component.

## Hear Rate Sensor

We receive an absolute, unit-less numerical value, not a BPM measurement. With the help of a [cardio zone table](https://customercare.geonaute.com/hc/en-gb/articles/205822622-WHAT-DO-THE-COLOUR-CARDIO-ZONES-MEAN-), we empirically determine the values to be:

| Zone   | Min. | Max. |
| ------ | ---- | ---- |
| Green  | n/a  | 550  |
| Orange | 550  | 800  |
| Red    | 800  | n/a  |

We will output the appropriate color for the range the value reads.

## GPS Sensor

In a more fleshed-out example we'd receive information from a real turn-by-turn Navigation API. Those are really expensive and work-intensive. So for the sake of the example, we just generate a random direction regardless of GPS input and output it.

## Orientation

We read the rotation on the axis value from the Mega, and subtract it from 180, then output it, showing how the person should move opposite to the inclination to counter-balance.
