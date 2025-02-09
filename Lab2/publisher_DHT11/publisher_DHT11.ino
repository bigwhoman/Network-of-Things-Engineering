#include "MqttClient.h"
#include "WifiClient.h"
#include "DHT.h" // DHT module library
#include <ArduinoJson.h>

char *ssid_wifi = "HIP";
char *pass_wifi = "bullshit1";

const char *mqtt_broker_ip = "172.20.10.2";
const int mqtt_broker_port = 1883;
const char *client_id = "publisher_DHT11";
const char *publish_topic = "temperature_topic";
WifiClient wifi_client(ssid_wifi, pass_wifi);
MqttClient mqtt_client(mqtt_broker_ip, mqtt_broker_port);

float old_temperature;
float old_humidity;

#define DHTPIN D13 // DHT11's data pin is connected to

#define DHTTYPE DHT11   // DHT type
DHT dht(DHTPIN, DHT11); // instantiate DHT object

void setup()
{
    old_temperature = 0;
    old_humidity = 0;
    Serial.begin(9600);
    wifi_client.connect();
    mqtt_client.connect(client_id);
    dht.begin(); // initialize the sensor
}

void loop()
{
    mqtt_client.check_connection(client_id);
    float humidity = dht.readHumidity();
    if (!isnan(humidity))
    {
        String humidity_str = String(humidity); // convert float to string
        Serial.print("Humidity: " + humidity_str + " %\n");
    }
    else
    {
        Serial.println("Humidity reading from DHT11 sensor failed!");
    }
    float temperature = dht.readTemperature();
    if (!isnan(temperature))
    {
        String temperature_str = String(temperature);
        // convert float to string

        Serial.print("Temperature: " + temperature_str + " *C\n");
    }
    else
    {
        Serial.println("Temperature reading from DHT11 sensor failed!");
    }
    delay(1000);

    if ((temperature != old_temperature) || (humidity != old_humidity))
    {
        DynamicJsonDocument doc(1024);

        doc["id"] = "publisher_DHT11";
        doc["temperature"] = temperature;
        doc["humidity"] = humidity;

        old_humidity = humidity;
        old_temperature = temperature;
        // Generate the prettified JSON and send it to the Serial port
        // serializeJsonPretty(doc, Serial);

        String json_doc;
        serializeJson(doc, json_doc);
        char buf[500];
        json_doc.toCharArray(buf, 500);
        mqtt_client.publish_message(publish_topic, buf);
        delay(5000);
    }
}