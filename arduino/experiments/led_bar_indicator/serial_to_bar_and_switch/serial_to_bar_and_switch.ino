const int ledPin = 9;   // Use the A5 pin for analogWrite
const int ledAnode = 8;
bool ledState = HIGH;

void setup() {
  pinMode(ledAnode, OUTPUT);
  pinMode(ledPin, OUTPUT);  // Set the LED pin as an output
  Serial.begin(9600);     // Initialize serial communication
}

void loop() {
  if (Serial.available() > 0) {
    String input = Serial.readString();  // Read the serial input as a string
    removeLastCharacter(input);

    if (input == "s") {
      // Toggle the state of pin 8
      ledState = !ledState;
      digitalWrite(ledAnode, ledState);
      Serial.println(ledState);
    }
    
    if(isStringInt(input)) {
      // Parse the string as an integer and set the LED brightness
      int brightness = input.toInt();
      if (brightness >= 0 && brightness <= 255) {
        analogWrite(ledPin, brightness);
        Serial.println(brightness);
      }
    }
    
  }
}


bool isStringInt(const String &str) {
  for (size_t i = 0; i < str.length(); i++) {
    if (!isdigit(str.charAt(i))) {
      return false; // If a non-digit character is found, it's not an integer.
    }
  }
  return true; // All characters are digits, so it's an integer.
}

void removeLastCharacter(String &str) {
  if (str.length() > 0) {
    str.remove(str.length() - 1);
  }
}
