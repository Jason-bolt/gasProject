// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
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
