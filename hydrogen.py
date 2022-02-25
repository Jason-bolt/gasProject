from machine import Pin, ADC
import time

mq5 = ADC(Pin(34))

while True:
    hydrogen = mq5.read()
    print(hydrogen)
    time.sleep(1)