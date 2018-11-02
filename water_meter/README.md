# Water Meter Overview

This implements a reader for the Recordall HRE-LCD water meter register. I
believe that this device uses the sensus protocol but I can't find an open
description of that.

The file hre-lcd-reader.py is some code I used to reverse engineer the protociol.

The HRE-LCD has three wires ground (black), power/clock(red), and data(green).
Data is marched out on the data line after a rising edge on the
power/clock line.

This also has an interface to a string of one-wire temperature
sensors.

Considering adding a Cl2 sensor:
https://www.aliexpress.com/item/ME3-Cl2-electrochemical-chlorine-sensor-for-industrial-use/32494309708.html
https://euro-gasman.com/gas-sensors/chlorine-cl2/gas-sensors-with-transmitters/4-8v-digital-i2cbus-transmitter.html
https://www.cooking-hacks.com/shop/sensors/gas


# Hardware
This device is a particle photon.

D0 drives the power/clock for the water meter through a 1k resister to
the base of a pnp transistor
D1 is the data and has a 1 k pulldown

The pnp transitor has the collector connected to the power/clock and is pulled up
to +5 via a 1 k resistor.
The emitter is connected to ground

D4 drives the one-wire bus and has a 2k pullup

# Particle Web API
## Device
Name: water_meter
ID: 310030000b47363339343638

curl https://api.particle.io/v1/devices/310030000b47363339343638/events?access_token=2d9d2e4cf3ec878b5c8d2dba54d8fc0d2b771bd3


Reset user counter

curl https://api.particle.io/v1/devices/310030000b47363339343638/user_reset \
  -d access_token=2d9d2e4cf3ec878b5c8d2dba54d8fc0d2b771bd3 \
  -d arg=not_required

Get hour usage
curl https://api.particle.io/v1/devices/310030000b47363339343638/hour_usage?access_token=2d9d2e4cf3ec878b5c8d2dba54d8fc0d2b771bd3

Note that the query with curl can't use -d to provice access_token


### vars
* `total_usage` : Total water usage (gal)
* `flow_rate`: instantaneous flow rate (gpm)
* `read_errors`: HRE read errors
* `hour_usage`
* `day_usage`
* `week_usage`
* `month_usage`
* `user_usage`: (not implemented yet)


### events
* rate: `flow_rate` and `total_usage` when whenever rate > 0
* usage: All the time based useages every hour, at the end of the reporting
period

### functions
* `user_reset(void)`: resets the user_usage counter (not implemented yet)


