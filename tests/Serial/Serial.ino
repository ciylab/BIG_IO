void setup() {
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
}

void loop() {
   delay(1000);
   Serial.println("I send");
}
