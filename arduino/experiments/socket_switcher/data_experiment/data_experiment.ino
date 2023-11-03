const uint8_t selectorPins[3] = {13, 12, 8};
const uint8_t pulseWritePin = 3;
const uint8_t dataWritePin = 2;


bool data[8] = {true, true, true, true, true, true, true, true};

void setup() {
  Serial.begin(9600);

  for(int selectorPin : selectorPins){
    pinMode(selectorPin, OUTPUT);
  }
  pinMode(pulseWritePin, OUTPUT);
  pinMode(dataWritePin, OUTPUT);

  digitalWrite(pulseWritePin, LOW);
  digitalWrite(dataWritePin, LOW);

  
  
}

void loop() {
  if (Serial.available() > 0) {
    uint8_t selected = Serial.parseInt();
    
    if(selected >= 8){  
      return; 
    }

    Serial.println("Selecting Pin..." + String(selected));
    selectPin(selected);
    Serial.println("Pin Selected");
    
    Serial.println("Writing Data..." + String(data[selected]));
    data[selected] = !data[selected];
    digitalWrite(dataWritePin, data[selected]);
    Serial.println("Data Written");

    Serial.println("Saving Data..." + String(data[selected]));
    digitalWrite(pulseWritePin, HIGH);
    delay(100);
    digitalWrite(pulseWritePin, LOW);
    Serial.println("Data Saved");

    for (uint8_t i = 0; i < 8; i++) {
      Serial.print(data[i]);
      Serial.print(" | ");
    }
    Serial.println();

    Serial.read();
  }
}


void selectPin(uint8_t input) {
  for (uint8_t i = 0; i < 3; i++) {
    digitalWrite(selectorPins[i], input & 1);
    input >>= 1;
  }
  return;
}


