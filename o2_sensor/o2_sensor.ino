// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int o2 = analogRead(A1);
  // print out the value you read:
  Serial.print("O2 = ");
  Serial.println(o2);

  delay(500);        // delay in between reads for stability
}
