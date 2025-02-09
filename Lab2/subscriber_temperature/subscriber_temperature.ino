#include "MqttClient.h"
#include "WifiClient.h"
#include <ArduinoJson.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define LED D13 // external LED is connected to board's

char *ssid_wifi = "HIP";
char *pass_wifi = "bullshit1";

const char *mqtt_broker_ip = "172.20.10.2";
const int mqtt_broker_port = 1883;
const char *client_id = "subscriber_DHT11";
const int num_subscribe_topics = 1;
String subscribe_topics[num_subscribe_topics] =
    {"temperature_topic"};
WifiClient wifi_client(ssid_wifi, pass_wifi);
MqttClient mqtt_client(mqtt_broker_ip, mqtt_broker_port,
                       subscribe_topics, num_subscribe_topics);

float temp[50];
int temp_cnt = 0;


float temperature = 0;
float humidity = 0;
float blink_delay = 100;
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
    Serial.begin(9600);
    wifi_client.connect();
    mqtt_client.connect(client_id);
    pinMode(LED, OUTPUT); // initialize LED as an output
    lcd.init();
    lcd.backlight();
}

void loop()
{
    mqtt_client.check_connection(client_id);
    String msg = mqtt_client.get_msg();
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, msg);
    float avg_temp = 0;
    temperature = doc["temperature"];
    temp[temp_cnt] = temperature;
    temp_cnt ++;
    if (temp_cnt >=50) {
      for(int i = 0; i < 50; i++){
          avg_temp += temp[i];  
      }
      avg_temp /= 50;
      temp_cnt = 0;
      if (avg_temp >= 10.0 && avg_temp < 20.0)
      {
          blink_delay = 2000;
      }
      else if (avg_temp >= 20.0 && avg_temp < 30.0)
      {
          blink_delay = 500;
      }
      else
      {
          blink_delay = 1000;
      }
    }
    digitalWrite(LED, HIGH); // turn the LED on (HIGH is the voltage level)
    delay(blink_delay);      // wait
    digitalWrite(LED, LOW);  // turn the LED off by making the voltage LOW
    delay(blink_delay);      // wait
    lcd.setCursor(0, 0);
    lcd.print("Temp. ");
    String temperature_str = String(temperature, 1);
    lcd.print(temperature_str);
    lcd.print((char)223); // celsius char
}
