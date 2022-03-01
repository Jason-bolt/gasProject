// Sensors Combined here
// MQ-5 
// MQ-4
// CCS811
// CJMCU-6814
// ANEMOMETER

#include <Arduino.h>
#include <Wire.h>
#include "ccs811.h"  // CCS811 library

// nWAKE not controlled via Arduino host, so connect CCS811.nWAKE to GND
CCS811 ccs811; 

int sensor = 2;
//  Diameter of the wind vane in mm
int vane_diameter = 120;

//  Calculating the vane circumference
float vane_circ = ((vane_diameter * 1.000) / 1000) * 3.1415;

//  Vane inefficiency factor (Should come from a comparison with a working vane)
float err = 7800.5;

// Defining defaults
int rotations = 0;
int trigger = 0;
int count = 0;
int sensorValue = 0;
float rots_per_second;
float windspeed;

const int R_0 = 945; //Change this to your own R0 measurements

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(sensor, INPUT);
  Serial.println("Starting measuring");

  // Enable I2C
  Wire.begin(); 
  
  // Enable CCS811
  ccs811.set_i2cdelay(50); // Needed for ESP8266 because it doesn't handle I2C clock stretch correctly
  bool ok= ccs811.begin();
  if( !ok ) Serial.println("setup: CCS811 begin FAILED");

  // Start measuring
  ok= ccs811.start(CCS811_MODE_1SEC);
  if( !ok ) Serial.println("setup: CCS811 start FAILED");

  while (!Serial)
    delay(10);     // will pause Zero, Leonardo, etc until serial console opens
}

// the loop routine runs over and over again forever:
void loop() {

  uint16_t eco2, etvoc, errstat, raw;
  ccs811.read(&eco2,&etvoc,&errstat,&raw); 
  
  // Print measurement results based on status
  if( errstat==CCS811_ERRSTAT_OK ) { 
    Serial.print("CCS811: ");
    Serial.print("eco2=");  Serial.print(eco2);     Serial.print(" ppm  ");
    Serial.print("etvoc="); Serial.print(etvoc);    Serial.print(" ppb  ");
    //Serial.print("raw6=");  Serial.print(raw/1024); Serial.print(" uA  "); 
    //Serial.print("raw10="); Serial.print(raw%1024); Serial.print(" ADC  ");
    //Serial.print("R="); Serial.print((1650*1000L/1023)*(raw%1024)/(raw/1024)); Serial.print(" ohm");
    Serial.println();
  } else if( errstat==CCS811_ERRSTAT_OK_NODATA ) {
    Serial.println("CCS811: waiting for (new) data");
  } else if( errstat & CCS811_ERRSTAT_I2CFAIL ) { 
    Serial.println("CCS811: I2C error");
  } else {
    Serial.print("CCS811: errstat="); Serial.print(errstat,HEX); 
    Serial.print("="); Serial.println( ccs811.errstat_str(errstat) ); 
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

  while (count < 6000){
    sensorValue = digitalRead(sensor);
//    Serial.println(sensorValue);
    if (sensorValue == 1 && trigger == 0){
      rotations = rotations + 1;
      trigger = 1;
    }
    if (sensorValue == 0){
      trigger = 0;
    }

//    Serial.println(rotations);

    count = count + 1;
    delay(1);
  }
  if (rotations == 1 && sensorValue == 1){
    rotations = 0;
  }
  rots_per_second = (rotations * 1.000) / 6000;
  windspeed = rots_per_second * vane_circ * err;
  Serial.print("Windspeed is ");
  Serial.print(windspeed, 5);
  Serial.println(" m/s");

  count = 0;
  rotations = 0;

  delay(500);        // delay in between reads for stability
}


float getMethanePPM() {
  float a2 = analogRead(A2); // get raw reading from sensor
  float v_o = a2 * 5 / 1023; // convert reading to volts
  float R_S = (5 - v_o) * 1000 / v_o; // apply formula for getting RS
  float PPM = pow(R_S / R_0, -2.95) * 1000; //apply formula for getting PPM
  return PPM; // return PPM value to calling function
}
