#include "distance.h"
#define LED D13
const int trigPin = D15;
const int echoPin = D14;

HCSR04 hcsr04(trigPin, echoPin);

void setup(){
    pinMode(LED, OUTPUT);
    Serial.begin(9600);
}

void loop(){
    float distance = hcsr04.calculate_distance();
    if(distance < 10){
        digitalWrite(LED, HIGH);
    } else { 
        digitalWrite(LED, LOW);
    }
}