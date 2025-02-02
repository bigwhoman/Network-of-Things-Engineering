#include "DHT.h"

#define DHTPIN D13 
#define LED D13
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHT11);
float old_temperature;
void setup(){
    pinMode(LED, OUTPUT);
    Serial.begin(9600);
    dht.begin();
}

void loop(){
    float humidity = dht.readHumidity();
    if (!isnan(humidity)){
        String humidity_str = String(humidity);
        Serial.print("Humidity: "+ humidity_str + "%\n");
    } else {
        Serial.println("Humidity reading from DHT11 failed");
    }
    float temperature = dht.readTemperature();
    if (!isnan( temperature))
    {
        String temperature_str = String(temperature);
        Serial.print ("Temperature: " + temperature_str + " *C\n") ;
        if(old_temperature != temperature){
            digitalWrite(LED, HIGH);
            delay(5000);
            digitalWrite(LED, LOW);
            old_temperature = temperature;
        }
    } else {
        Serial.println("Temperature reading from DHT11 sensor failed!");
    }
    delay (1000);
}