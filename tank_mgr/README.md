# particle_tank_mgr

This is the water tank manager device. It talks with the following devices:
  * A string of 18B20s to monitor the temperature of the plumbing (1-wire on D4)
  * A pressure sensor (analog)
  * A water level hight sensor to read the tank levels (serial)


starting dev with "playpen_beast", 24002c000447363333343435 as the particle

To see events...

curl https://api.particle.io/v1/devices/events?access_token=a9760ba797492d593b6f0f11d10a1024bea5cc6d

curl https://api.particle.io/v1/devices/24002c000447363333343435/led \
  -d access_token=a9760ba797492d593b6f0f11d10a1024bea5cc6d \
  -d arg=on


# Controller
This is a Particle photon plugged into on adaptor board. The board brings out
```
VIN - 5 VDC power supply
GND - power suppy ground

D5 - OW_Vcc   RJ45 2
D4 - OW_data  RJ45 4
D3 - OW_gnd   RJ45 5

TX - Water height sensor
RX - 
```

D4 has a 2k pullup to V3.3 and a soldered in DS1820, address
f2f2ed010800.


# Temperature sensor cable
This is a 30' length of cat5 with 18B20 sensors embedded along the
lenght. I use the TIA86B pinouts for the termination of the cable into
an RJ45 plug.

RJ45 Pin | Wire color | Function
----     | --------   | ----
2        | orange     | OW_Vcc
4        | blue       | D0
5        | blue/wht   | OW_gnd

DS18B20 Sensors, starting with closest to plug

No. | address
-- | ------------
1  | ff2e55321801
2  | fffb05321802
3  | ffa451321801
4  | ff0fee311802
5  | ff5e4f321801
6  | ff7e07321802

