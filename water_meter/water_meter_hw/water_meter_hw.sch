EESchema Schematic File Version 4
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Device:Q_NPN_ECB Q1
U 1 1 5BD1D39E
P 3400 2800
F 0 "Q1" H 3591 2846 50  0000 L CNN
F 1 "NPN" H 3591 2755 50  0000 L CNN
F 2 "" H 3600 2900 50  0001 C CNN
F 3 "~" H 3400 2800 50  0001 C CNN
	1    3400 2800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5BD1E16B
P 3500 3150
F 0 "#PWR?" H 3500 2900 50  0001 C CNN
F 1 "GND" H 3505 2977 50  0000 C CNN
F 2 "" H 3500 3150 50  0001 C CNN
F 3 "" H 3500 3150 50  0001 C CNN
	1    3500 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	3500 3150 3500 3000
$Comp
L Device:R R1
U 1 1 5BD1E5DA
P 3500 2300
F 0 "R1" H 3570 2346 50  0000 L CNN
F 1 "1k" H 3570 2255 50  0000 L CNN
F 2 "" V 3430 2300 50  0001 C CNN
F 3 "~" H 3500 2300 50  0001 C CNN
	1    3500 2300
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 5BD1E7C8
P 3500 2000
F 0 "#PWR?" H 3500 1850 50  0001 C CNN
F 1 "+5V" H 3515 2173 50  0000 C CNN
F 2 "" H 3500 2000 50  0001 C CNN
F 3 "" H 3500 2000 50  0001 C CNN
	1    3500 2000
	1    0    0    -1  
$EndComp
Wire Wire Line
	3500 2150 3500 2000
$Comp
L Device:R R2
U 1 1 5BD1E90C
P 3000 2800
F 0 "R2" V 3207 2800 50  0000 C CNN
F 1 "1k" V 3116 2800 50  0000 C CNN
F 2 "" V 2930 2800 50  0001 C CNN
F 3 "~" H 3000 2800 50  0001 C CNN
	1    3000 2800
	0    -1   -1   0   
$EndComp
$Comp
L Connector:Screw_Terminal_01x03 J1
U 1 1 5BD1EDFB
P 2000 2250
F 0 "J1" H 1920 2567 50  0000 C CNN
F 1 "HRE" H 1920 2476 50  0000 C CNN
F 2 "" H 2000 2250 50  0001 C CNN
F 3 "~" H 2000 2250 50  0001 C CNN
	1    2000 2250
	-1   0    0    -1  
$EndComp
Text GLabel 1850 2150 0    50   Input ~ 0
green
Text GLabel 1850 2350 0    50   Input ~ 0
red
Text GLabel 1850 2250 0    50   Input ~ 0
black
Wire Wire Line
	3150 2800 3200 2800
Wire Wire Line
	3500 2600 3500 2500
Connection ~ 3500 2500
Wire Wire Line
	3500 2500 3500 2450
Wire Wire Line
	3500 2500 3200 2500
Wire Wire Line
	3200 2500 3200 2350
Wire Wire Line
	3200 2350 2200 2350
$Comp
L power:GND #PWR?
U 1 1 5BD1FC85
P 2350 2450
F 0 "#PWR?" H 2350 2200 50  0001 C CNN
F 1 "GND" H 2355 2277 50  0000 C CNN
F 2 "" H 2350 2450 50  0001 C CNN
F 3 "" H 2350 2450 50  0001 C CNN
	1    2350 2450
	1    0    0    -1  
$EndComp
Wire Wire Line
	2350 2450 2350 2250
Wire Wire Line
	2350 2250 2200 2250
$Comp
L Device:R R3
U 1 1 5BD1FEEE
P 2500 1900
F 0 "R3" H 2570 1946 50  0000 L CNN
F 1 "1k" H 2570 1855 50  0000 L CNN
F 2 "" V 2430 1900 50  0001 C CNN
F 3 "~" H 2500 1900 50  0001 C CNN
	1    2500 1900
	1    0    0    -1  
$EndComp
Wire Wire Line
	2200 2150 2500 2150
Wire Wire Line
	2500 2150 2500 2050
$Comp
L power:+5V #PWR?
U 1 1 5BD2054A
P 2500 1600
F 0 "#PWR?" H 2500 1450 50  0001 C CNN
F 1 "+5V" H 2515 1773 50  0000 C CNN
F 2 "" H 2500 1600 50  0001 C CNN
F 3 "" H 2500 1600 50  0001 C CNN
	1    2500 1600
	1    0    0    -1  
$EndComp
Wire Wire Line
	2500 1600 2500 1750
Text GLabel 2700 2800 0    50   Input ~ 0
particle_D0
Wire Wire Line
	2700 2800 2850 2800
Text GLabel 2750 2150 2    50   Input ~ 0
particle_D1
Wire Wire Line
	2750 2150 2500 2150
Connection ~ 2500 2150
Text Notes 7400 7500 0    50   ~ 0
HRE and 1-wire interface for water meter
$Comp
L RF_Module:Particle_P1 U?
U 1 1 5BD22416
P 8850 2950
F 0 "U?" H 8850 5028 50  0000 C CNN
F 1 "Particle_P1" H 8850 4937 50  0000 C CNN
F 2 "RF_Module:Particle_P1" H 8850 2950 50  0001 C CNN
F 3 "https://docs.particle.io/datasheets/p1-datasheet/" H 8850 2950 50  0001 C CNN
	1    8850 2950
	1    0    0    -1  
$EndComp
Text GLabel 7300 1750 0    50   Input ~ 0
particle_D0
Text GLabel 7300 1900 0    50   Input ~ 0
particle_D1
$EndSCHEMATC
