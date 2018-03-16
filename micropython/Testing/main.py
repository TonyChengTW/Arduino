import network
import time
from machine import Pin

sta_if = network.WLAN(network.STA_IF) # create station interface
sta_if.active(True)       # activate the interface
sta_if.scan()             # scan for access points
sta_if.isconnected()      # check if the station is connected to an AP
sta_if.connect('CloudCube_TPE_Office', 'cloudcube54729082') # connect to an AP
sta_if.config('mac')      # get the interface's MAC adddress
print ("sta_if.ifconfig=")
sta_if.ifconfig()         # get the interface's IP/netmask/gw/DNS addresses

ap_if = network.WLAN(network.AP_IF) # create access-point interface
ap_if.active(True)         # activate the interface
ap_if.config(essid='ESP-micropython-Tony', authmode=network.AUTH_WPA_WPA2_PSK, password="0123456789") # set the ESSID of the access point


while True:
    p2 = Pin(2, Pin.OUT)   # create output pin on GPIO16
    p2.on()                 # set pin to "on" (high) level
    time.sleep(1)
    p2.off()    # set pin to "off" (low) level
    time.sleep(1)
    p2.value(1)             # set pin to on/high
"""
p2 = Pin(2, Pin.IN)     # create input pin on GPIO2
print(p2.value())       # get value, 0 or 1
p4 = Pin(4, Pin.IN, Pin.PULL_UP) # enable internal pull-up resistor
p5 = Pin(5, Pin.OUT, value=1) # set pin high on creation
"""
