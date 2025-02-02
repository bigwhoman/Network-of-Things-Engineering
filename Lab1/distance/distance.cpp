#include "distance.h"
#include <Arduino.h>

HCSR04::HCSR04(int trigPin, int echoPin){
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    _trigPin = trigPin;
    _echoPin = echoPin;
}

float HCSR04::calculate_distance(){
    digitalWrite(_trigPin, LOW);
    delayMicroseconds(10);
    digitalWrite(_trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(_trigPin, LOW);

    long duration = pulseIn(_echoPin, HIGH);
    float distance = duration * 0.034 / 2;
    return distance;
}