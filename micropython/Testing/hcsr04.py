#main.py
import ssd1306
from machine import Pin, I2C
from hcsr04 import HCSR04

hcsr = HCSR04(trigger_pin = 0, echo_pin = 14)
i2c = I2C(scl=Pin(5), sda=Pin(4))
oled = ssd1306.SSD1306_I2C(128, 64, i2c)

while True:
    print("Measuring.")
    oled_distance = "Dist: %3.1fcm" % hcsr.distance_cm()
    oled.fill(0)
    oled.text(oled_distance, 0, 16)
    custom_char(oled, 11, 0, bitlist)
    oled.show()
    time.sleep(0.3)
