void setup() {
  pinMode(DAC, OUTPUT);
  analogWriteResolution(12);
}
 
void loop() {
  analogWrite(DAC, 4095);
  delay(500); 
  analogWrite(DAC, 0);
  delay(500); 
}

