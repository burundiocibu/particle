# Tank Manager Overview

This is the water tank manager device. It talks with the following devices:
  * A string of 18B20s to monitor the temperature of the plumbing (1-wire on D4)
  * A pressure sensor (analog)
  * A water level hight sensor to read the tank levels (serial)

# Hardware
This is a Particle photon plugged into on adaptor board. The board brings out

Pin | Function  | Connection
--- | --------  | ----------
VIN |           | power supply +5 VDC
GND |           | power suppy ground
D5  | `OW_Vcc`  | J1-2
D4  | `OW_data` | J1-4
D3  | `OW_gnd`  | J1-5
TX  | `WH_tx`   | J2-tip
RX  | `WH_rx`'  | J2-ring

* J1 is an RJ45 jack
* J2 is a 1/8" trs jack, shield connected to ground

D4 has a 2k pullup to V3.3 and a soldered in DS1820, address
0x10f2f2ed010800cb

## Temperature sensor cable
This is a 25' length of cat5 with 18B20 sensors embedded along the
lenght. I use the TIA86B pinouts for the termination of the cable into
an RJ45 plug.

RJ45 Pin | Wire color | Function
----     | --------   | ----
2        | orange     | `OW_Vcc`
4        | blue       | `D0`
5        | blue/wht   | `OW_gnd`

DS18B20 sensors addresses, starting with closest to plug

No. | address         | location
-- | ---------------- | --------
1  | 28ff99e33118017c | Ambient
2  | 28ff870232180262 | Pump head
3  | 28ff2e553218011e | pipe going into ground to house
4  | 28fffb05321802a8 |
5  | 28ffa45132180166 |
5  | 28ff0fee31180228 |
7  | 28ff5e4f32180150 |
8  | 28ff7e07321802b6 | pipe by valve going into tank



# Photon Web API

## Device
Photon particle
Name: tank_mgr
ID: 24002c000447363333343435

Events:

curl https://api.particle.io/v1/devices/24002c000447363333343435/events?access_token=2d9d2e4cf3ec878b5c8d2dba54d8fc0d2b771bd3



## vars
* `tmin_pipe`
* `tmax_pipe`
* `t_photon`
* `t_ambient`
