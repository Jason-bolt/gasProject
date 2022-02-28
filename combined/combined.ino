#include <Arduino.h>
#include <Wire.h>
#include "Adafruit_SHT31.h"

bool enableHeater = false;
uint8_t loopCnt = 0;

Adafruit_SHT31 sht31 = Adafruit_SHT31();

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  while (!Serial)
    delay(10);     // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("SHT31 test");
  if (! sht31.begin(0x44)) {   // Set to 0x45 for alternate i2c addr
    Serial.println("Couldn't find SHT31");
    while (1) delay(1);
  }

  Serial.print("Heater Enabled State: ");
  if (sht31.isHeaterEnabled())
    Serial.println("ENABLED");
  else
    Serial.println("DISABLED");
}

// the loop routine runs over and over again forever:
void loop() {

  float t = sht31.readTemperature();
  float h = sht31.readHumidity();

  if (! isnan(t)) {  // check if 'is not a number'
    Serial.print("Temp *C = "); Serial.print(t); Serial.print("\t\t");
  } else { 
    Serial.println("Failed to read temperature");
  }
  
  if (! isnan(h)) {  // check if 'is not a number'
    Serial.print("Hum. % = "); Serial.println(h);
  } else { 
    Serial.println("Failed to read humidity");
  }
  
  // read the input on analog pin 0:
  int o2 = analogRead(A1);
  // print out the value you read:
  Serial.print("O2 = ");
  Serial.println(o2);

  int mq5SensorValue = analogRead(A0);
  // print out the value you read:
  Serial.print("Hydrogen: ");
  Serial.println(mq5SensorValue);

  int mq4SensorValue = analogRead(A2);
  // print out the value you read:
  Serial.print("Methane: ");
  Serial.println(mq4SensorValue);

  // read the input on analog pin 0:
  int no2 = analogRead(A3);
  int nh3 = analogRead(A4);
  int co = analogRead(A5);
  // print out the value you read:
  Serial.print("NO2 = ");
  Serial.println(no2);

  Serial.print("NH3 = ");
  Serial.println(nh3);

  Serial.print("CO = ");
  Serial.println(co);

  delay(500);        // delay in between reads for stability
}


float getMethanePPM(){
   float a2 = analogRead(A2); // get raw reading from sensor
   float v_o = a2 * 5 / 1023; // convert reading to volts
   float R_S = (5-v_o) * 1000 / v_o; // apply formula for getting RS
   float PPM = pow(R_S/R_0,-2.95) * 1000; //apply formula for getting PPM
   return PPM; // return PPM value to calling function
}
