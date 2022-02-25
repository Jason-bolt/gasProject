from machine import Pin
import time

sensor = Pin(12, Pin.IN)
vane_diameter = 120
vane_circ = ((vane_diameter * 1.000) / 1000) * 3.1415
err = 703.5
rotations = 0
trigger = 0
count = 0
sensorValue = 0
rots_per_second = 0.0
windspeed = 0.0

print("Starting Measurement")

while True:
#     print(sensor.value())
    while count < 1000:
        sensorValue = sensor.value()
        if sensorValue == 1 and trigger == 0:
            rotations = rotations + 1
            trigger = 1
        if sensorValue == 0:
            trigger = 0
        count += 1
        
        print("rotations = ", rotations)
        
        time.sleep_ms(10)
    
    if rotations == 1 and sensorValue == 1:
        rotations = 0
    
    rots_per_second = (rotations * 1.000) / 1000
    windspeed = rots_per_second * vane_circ * err
    
    print("Windspeed = ", windspeed, " m/s")
    time.sleep(3)
        