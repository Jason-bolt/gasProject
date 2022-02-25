//int hall = 2;
//
//// the setup routine runs once when you press reset:
//void setup() {
//  // initialize serial communication at 9600 bits per second:
//  Serial.begin(9600);
//  // make the pushbutton's pin an input:
//  pinMode(hall, INPUT);
//}
//
//// the loop routine runs over and over again forever:
//void loop() {
//  // read the input pin:
//  int hallState = digitalRead(hall);
//  // print out the state of the button:
//  Serial.println(hallState);
//  delay(1);        // delay in between reads for stability
//}

int sensor = 2;
//  Diameter of the wind vane in mm
int vane_diameter = 120;

//  Calculating the vane circumference
float vane_circ = ((vane_diameter * 1.000) / 1000) * 3.1415;

//  Vane inefficiency factor (Should come from a comparison with a working vane)  
float err = 703.5;

// Defining defaults 
int rotations = 0;
int trigger = 0;
int count = 0;
int sensorValue = 0;
float rots_per_second;
float windspeed;



void setup() {
  Serial.begin(9600);
  pinMode(sensor, INPUT);
  
  Serial.println("Starting measuring");
}

void loop() {
  while (count < 1000){
    sensorValue = digitalRead(sensor);
    Serial.println(sensorValue);
    if (sensorValue == 1 && trigger == 0){
      rotations = rotations + 1;
      trigger = 1;
    }
    if (sensorValue == 0){
      trigger = 0;
    }

    Serial.println(rotations);

    count = count + 1;
    delay(1);
  }

//  Checking for falls starts
  if (rotations == 1 && sensorValue == 1){
    rotations = 0;
  }

//  Calculating wind speed after 10 seconds
  rots_per_second = (rotations * 1.000) / 1000;
  windspeed = rots_per_second * vane_circ * err;
//
//  Serial.println(rots_per_second);
//  delay(500);

  Serial.print("Windspeed is ");
  Serial.print(windspeed);
  Serial.println(" m/s");

  delay(500);

  count = 0;
  rotations = 0;
}
