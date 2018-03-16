from machine import Pin, I2C

i2c = I2C(scl=Pin(5), sda=Pin(4))
i2c.scan()