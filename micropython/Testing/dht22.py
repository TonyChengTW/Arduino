import dht
import machine
import time

print("Starting DHT22.")
d = dht.DHT22(machine.Pin(12))

while True:
    print("Measuring.")

    retry = 0
    while retry < 3:
        try:
            d.measure()
            break
        except:
            retry = retry + 1
            print(".", end = "")

    print("")

    if retry < 3:
        print("Temperature: %3.1f °C" % d.temperature())
        print("Humidity: %3.1f %% RH" % d.humidity())
    time.sleep(5)
