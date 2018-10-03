#!/usr/bin/env python
""" Module to read data from a Badger HRE e LCD encoder.
I _think_ this device uses a variant of the sensus protocol
KG44?Q45484=0444444V;RB000000022;IB018435683
"""

import RPi.GPIO as gpio
import time
import cPickle as pickle
import binascii
import bitarray


class BadgerReader:
    def __init__(self, clk_pin=24, data_pin=23, low_sleep=0.005, high_sleep=0.005):
        self.clk_pin=clk_pin
        self.data_pin=data_pin
        self.low_sleep = low_sleep
        self.high_sleep = high_sleep
        self.debug=0
        gpio.setmode(gpio.BCM)
        gpio.setup(self.clk_pin, gpio.OUT)
        gpio.setup(self.data_pin, gpio.IN)
        gpio.output(self.clk_pin, gpio.HIGH)

    def readBit(self):
        gpio.output(self.clk_pin, gpio.LOW)
        time.sleep(self.low_sleep)
        gpio.output(self.clk_pin, gpio.HIGH)
        time.sleep(self.high_sleep)
        return gpio.input(self.data_pin)

    def readBlock(self):
        """Read a 520 bit block from meter """
        buff=[]
        # First search for 62 bits of '1'
        run=0
        while run < 62:
            if self.readBit():
                run+=1
            else:
                run=0
        # Now just read off 46 10 bit words
        for b in range(46*10):
            buff.append(self.readBit())
        return bitarray.bitarray(buff)

    def decodeBlock(self, bits):
        msg=''
        for n in range(0,len(bits),10):
            w = bits[n+1:n+8]
            w.reverse()
            msg+=chr(int(w.to01(),2))
            p = w.count() & 0x1
            if p != bits[n+8]:
                print("Parity error")
        if self.debug: print(msg)
        v=dict()
        v['KG'] = msg[2:4]
        v['Q'] = msg[6:21]
        v['RB'] = int(msg[msg.find(";RB")+3:msg.find(";IB")])
        v['IB'] = msg[msg.find(";IB")+3:]
        return v

if __name__ == "__main__":
    br = BadgerReader(clk_pin=24, data_pin=23)
    block = br.readBlock()
    data = br.decodeBlock(block)
    print data['RB']/100.0, "gal"
    gpio.cleanup()
