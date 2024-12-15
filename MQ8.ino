const int AOUTpin = 26; // the AOUT pin of the hydrogen sensor goes into analog pin 36 (VP) of the ESP32
const int DOUTpin = 13; // the DOUT pin of the hydrogen sensor goes into digital pin 13 of the ESP32
const int ledPin = 2; // the anode of the LED connects to digital pin 2 of the ESP32

int limit = 1000;
int value;

void setup() {
  Serial.begin(115200); // sets the baud rate
  pinMode(DOUTpin, INPUT); // sets the pin as an input to the ESP32
  pinMode(ledPin, OUTPUT); // sets the pin as an output of the ESP32
}

void loop() {
  value = analogRead(AOUTpin); // reads the analog value from the hydrogen sensor's AOUT pin
  limit = digitalRead(DOUTpin); // reads the digital value from the hydrogen sensor's DOUT pin
  Serial.print("Hydrogen value: ");
  Serial.println(value); // prints the hydrogen value
  Serial.print("Limit: ");
  Serial.println(limit); // prints the limit reached as either LOW or HIGH (above or underneath)
  delay(1000);
  if (limit == HIGH) {
    digitalWrite(ledPin, HIGH); // if limit has been reached, LED turns on as status indicator
  } else {
    digitalWrite(ledPin, LOW); // if threshold not reached, LED remains off
  }
}
