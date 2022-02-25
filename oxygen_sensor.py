from machine import Pin, ADC
import time

VRefer = 3.3

adcPin = ADC(Pin(35))

def readO2Vout():
    sum = 0;
    for i in range(0, 32):
        sum += adcPin.read()
    sum >>= 5
    MeasuredVout = sum * (VRefer / 4095.0)
    return MeasuredVout


def readConcentration():
    # Vout samples are with reference to 3.3V
    MeasuredVout = readO2Vout()
    
    #float Concentration = FmultiMap(MeasuredVout, VoutArray,O2ConArray, 6);
    #when its output voltage is 2.0V,
    Concentration = MeasuredVout * 0.21 / 2.0
    Concentration_Percentage=Concentration * 100
    return Concentration_Percentage


while True:
    print("Vout = ", readO2Vout(), end='')
    print(" V, Concentration of O2 is ", readConcentration())
    time.sleep(1)
    
    


