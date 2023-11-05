#define voltmeterPin A5


void setup(){
    Serial.begin(9600);
    pinMode(voltmeterPin, INPUT);
    Serial.println("Voltmeter Ready");

}



void loop(){

    Serial.println(analogRead(voltmeterPin));
    delay(17);
}