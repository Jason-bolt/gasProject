// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int mq4SensorValue = analogRead(A2);
  // print out the value you read:
  Serial.println(mq4SensorValue);
  delay(1);        // delay in between reads for stability
}
