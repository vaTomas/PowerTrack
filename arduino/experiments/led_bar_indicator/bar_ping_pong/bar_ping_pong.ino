const int ledPin = 9;  // Use the A5 pin for analogWrite

void setup() {
  pinMode(ledPin, OUTPUT);  // Set the LED pin as an output
}

void loop() {
  // Gradually increase brightness
  for (int brightness = 0; brightness <= 255; brightness++) {
    analogWrite(ledPin, brightness);  // Set LED brightness
    delay(10);  // Wait for a short duration
  }

  // Gradually decrease brightness
  for (int brightness = 255; brightness >= 0; brightness--) {
    analogWrite(ledPin, brightness);  // Set LED brightness
    delay(10);  // Wait for a short duration
  }
}
