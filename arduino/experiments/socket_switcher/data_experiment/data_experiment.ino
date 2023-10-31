const uint8_t selectorPins[5] = {4, 5, 6, 7, 8};
const uint8_t pulseWritePin = 2;
const uint8_t dataWritePin = 3;

bool data[5] = {0, 0, 0, 0, 0};

void setup() {
  Serial.begin(9600);

  digitalWrite(pulseWritePin, LOW);

  for(int pin : selectorPins){
    pinMode(pin, OUTPUT);
  }
  pinMode(pulseWritePin, OUTPUT);
  pinMode(dataWritePin, OUTPUT);


  digitalWrite(dataWritePin, LOW);

  
  
}

void loop() {
  if (Serial.available() > 0) {
    uint8_t selected = Serial.parseInt();
    if(selected >= 5){  break; }

    selectPin(selected);

    data[selected] = !data[selected];
    digitalWrite(dataWritePin, data[selected]);

    digitalWrite(pulseWritePin, HIGH);
    digitalWrite(pulseWritePin, LOW);

    Serial.read();
  }
}


void selectPin(uint8_t number){
  for(uint8_t i = 0; i < 5; i++){
    if(i == number){
      digitalWrite(selectorPins[i], LOW);
    }
    else{
      digitalWrite(selectorPins[i], HIGH);
    }
  }
}
