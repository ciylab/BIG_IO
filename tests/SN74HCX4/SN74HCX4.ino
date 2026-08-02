/*
 * 
 */

int outPin = PB11; // digital output to 74HC
int inPin = PB10; // analog input from 74HC
int value = 0;  // value read after 74HC

void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(outPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(outPin, HIGH);
  value = digitalRead(inPin);
  Serial.print("HIGH: ");
  Serial.println(value); // 8
  delay(1000);

  digitalWrite(outPin, LOW);
  value = digitalRead(inPin);
  Serial.print("LOW: ");
  Serial.println(value); // 1010
  delay(1000);
}

