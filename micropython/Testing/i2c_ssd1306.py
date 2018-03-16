#main.py
import dht, time
import ssd1306
from machine import Pin, I2C

i2c = I2C(scl=Pin(5), sda=Pin(4))
oled = ssd1306.SSD1306_I2C(128, 64, i2c)
bitlist=[(2,0),(3,0),(1,1),(4,1),(1,2),(4,2),(2,3),(3,3)]

DHTPIN = Pin(12, Pin.IN)
dht22 = dht.DHT22(DHTPIN)



def custom_char(oled, x, y, bitlist, col=1):
   for i in bitlist:
       oled.pixel(x*8+i[0], y*8+i[1], col)

dht22.measure()

while True:
    print("Measuring.")
    retry = 0
    while retry < 3:
        try:
            dht22.measure()
            break
        except:
            retry = retry + 1
            print(".")

    print("")

    if retry < 3:
        oled_temp = "Temp: %3.2f C" % dht22.temperature()
        oled_hum = "Hum: %3.2f %% RH" % dht22.humidity()
        oled.fill(0)
        oled.text(oled_temp, 0, 0)
        oled.text(oled_hum, 0, 8)
        custom_char(oled, 11, 0, bitlist)
        oled.show()
    time.sleep(1)
