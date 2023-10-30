const int ledPin = 9;  // Use the A5 pin for analogWrite

void setup() {
  pinMode(ledPin, OUTPUT);  // Set the LED pin as an output
  Serial.begin(9600);     // Initialize serial communication
}

void loop() {
  if (Serial.available() > 0) {
    Serial.print("Hi");
    int brightness = Serial.parseInt(); // Read an integer from the serial port
    if (brightness >= 0 && brightness <= 255) {
      analogWrite(ledPin, brightness);  // Set LED brightness
    }
    Serial.read();
  }
}
