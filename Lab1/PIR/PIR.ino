#include "PIR.h"
#define LED D13
const int pirSensor = D15;

PIR pir(pirSensor);

void setup(){
    pinMode(LED, OUTPUT);
    Serial.begin(9600);
}

void loop(){
    bool is_motion = pir.detect_motion();
    if(is_motion){
        digitalWrite(LED, HIGH);
    } else { 
        digitalWrite(LED, LOW);
    }
    delay(1000);
}
