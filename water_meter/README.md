# water_meter

This implements a reader for the Recordall HRE-LCD water meter register. I
believe that this device uses the sensus protocol but I can't find an open
description of that.

The file hre-lcd-reader.py is some code I used to reverse engineer the protociol.

The HRE-LCD has three wires ground (black), power/clock(red), and data(green).
Data is marched out on the data line after a rising edge on the power/clock line.

# Hardware setup

D0 drives the power/clock through a 1k resister to the base of a pnp transistor
D1 is the data and has a 1 k pulldown

The pnp transitor has the collector connected to the power/clock and is pulled up
to +5 via a 1 k resistor.
The emitter is connected to ground
