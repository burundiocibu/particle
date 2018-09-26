# particle_tank_mgr

This is the water tank manager device. It talks with the following devices:
  * A string of 18B20s to monitor the temperature of the plumbing (1-wire on D4)
  * A couple relays to turn on/off heater tapes to keep the plumbing warm (GPIO)
  * A pressure sensor
  * A water level hight sensor to read the tank levels (serial)


starting dev with "playpen_beast", 24002c000447363333343435 as the particle

To see events...

curl https://api.particle.io/v1/devices/events?access_token=a9760ba797492d593b6f0f11d10a1024bea5cc6d

curl https://api.particle.io/v1/devices/24002c000447363333343435/led \
  -d access_token=a9760ba797492d593b6f0f11d10a1024bea5cc6d \
  -d arg=on


# Controller
Particle plugged into on adaptor board
```
VIN/GND -- 5VDC supply

D5 - OW_Vcc   RJ45 2
D4 - OW_data  RJ45 4
D3 - OW_gnd   RJ45 5

TX - 
```

D4 has a 2k pullup to V3.3 and a soldered in DS1820, address
f2f2ed010800


# Temperature sensor cable
This is a 30' length of cat5 with 18B20 sensors embedded along the
lenght. I use the TIA86B pinouts

RJ45 Pin | Wire color | Function
----+--------+----
2   | Orange | Vcc
4   | blue | D0
5   | blue/wht | Gnd

Sensors, starting with closest to plug
num | address
----+-------------
  1 | ff2e55321801
  2 | fffb05321802
  3 | ffa451321801
  4 | ff0fee311802
  5 | ff5e4f321801
  6 | ff7e07321802

#### ```/src``` folder:  
This is the source folder that contains the firmware files for your project. It should *not* be renamed. 
Anything that is in this folder when you compile your project will be sent to our compile service and compiled into a firmware binary for the Particle device that you have targeted.

If your application contains multiple files, they should all be included in the `src` folder. If your firmware depends on Particle libraries, those dependencies are specified in the `project.properties` file referenced below.

#### ```.ino``` file:
This file is the firmware that will run as the primary application on your Particle device. It contains a `setup()` and `loop()` function, and can be written in Wiring or C/C++. For more information about using the Particle firmware API to create firmware for your Particle device, refer to the [Firmware Reference](https://docs.particle.io/reference/firmware/) section of the Particle documentation.

#### ```project.properties``` file:  
This is the file that specifies the name and version number of the libraries that your project depends on. Dependencies are added automatically to your `project.properties` file when you add a library to a project using the `particle library add` command in the CLI or add a library in the Desktop IDE.

## Adding additional files to your project

#### Projects with multiple sources
If you would like add additional files to your application, they should be added to the `/src` folder. All files in the `/src` folder will be sent to the Particle Cloud to produce a compiled binary.

#### Projects with external libraries
If your project includes a library that has not been registered in the Particle libraries system, you should create a new folder named `/lib/<libraryname>/src` under `/<project dir>` and add the `.h`, `.cpp` & `library.properties` files for your library there. Read the [Firmware Libraries guide](https://docs.particle.io/guide/tools-and-features/libraries/) for more details on how to develop libraries. Note that all contents of the `/lib` folder and subfolders will also be sent to the Cloud for compilation.

## Compiling your project

When you're ready to compile your project, make sure you have the correct Particle device target selected and run `particle compile <platform>` in the CLI or click the Compile button in the Desktop IDE. The following files in your project folder will be sent to the compile service:

- Everything in the `/src` folder, including your `.ino` application file
- The `project.properties` file for your project
- Any libraries stored under `lib/<libraryname>/src`
