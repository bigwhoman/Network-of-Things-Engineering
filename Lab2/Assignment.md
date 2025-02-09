# Assignment 1

## (a)
Difference between publisher-subscriber and client-server is that the publisher-subscriber is an asyncronous event based model where no direct and 2 way communication is held as opposed to client server which we have a 2 way, direct communication which is also synchronous.

## (b)
Topics are actually like queues which subscribers subscribe to them. Like one topic would be interesting for a subscriber and when an event is published to that queue/topic, the subscriber would take it and do something while other topics might not be of use to it.

## (c)

Like push-notification applications use the publish-subscribe model because there is no need for a 2 way communication, just something triggers an event and then the subscriber would get it and do something. Also client-server model could give us redundancy.

# Assignment 2

## Subscriber : 

### Sub.ino

``` cpp
#include "Sub.h"
#include "WifiClient.h"

char *ssid_wifi = "ssid";
char *pass_wifi = "pass";

const char *mqtt_broker_ip = "172.20.10.2";
const int mqtt_broker_port = 1883;
const char *client_id = "sub";
const int num_subscribe_topics = 1;
String old_msg = "";
String subscribe_topics[num_subscribe_topics] =
    {"toast"};
const char *publish_topic = "toast";
WifiClient wifi_client(ssid_wifi, pass_wifi);
Subscriber subscriber(mqtt_broker_ip, mqtt_broker_port,
                       subscribe_topics, num_subscribe_topics);

void setup()
{
    Serial.begin(9600);
    wifi_client.connect();
    subscriber.connect(client_id);
}

void loop()
{
    subscriber.check_connection(client_id);
    String msg = subscriber.get_msg();
    if (msg != old_msg){
        Serial.println("New Message arrived : " + msg);
        old_msg = msg;
    }
}
```

### Sub.cpp

``` cpp
#include "Sub.h"
#include <MQTT.h>
#include <ESP8266WiFi.h>

WiFiClient _wifi_client;
String _msg;
String _topic;
int _num_subscribe_topics;

Subscriber::Subscriber(const char *mqtt_broker_ip, const int mqtt_broker_port)
{
    _mqtt_client.begin(mqtt_broker_ip, _wifi_client);
}

Subscriber::Subscriber(const char *mqtt_broker_ip, const int mqtt_broker_port, String *subscribe_topics, const int num_subscribe_topics)
{
    _mqtt_client.begin(mqtt_broker_ip, _wifi_client);
    _subscribe_topics = subscribe_topics;
    _num_subscribe_topics = num_subscribe_topics;
}

void callback(String &topic, String &payload)
{

    // Serial.println("Message arrived [" + topic + "]: " +
    //                payload);
    _msg = payload;
    _topic = topic;
}

void Subscriber::connect(const char *client_id)
{
    Serial.print("Connecting to MQTT broker... ");
    while (!_mqtt_client.connect(client_id, "public",
                                 "public"))
    {
        Serial.print(".");
        delay(1000);
    }
    Serial.println("done!");
    for (int i = 0; i < _num_subscribe_topics; i++)
    {
        _mqtt_client.onMessage(callback);
        _mqtt_client.subscribe(_subscribe_topics[i]);
        Serial.println("Subscribed to topic: " +
                       _subscribe_topics[i]);
    }
}


void Subscriber::check_connection(const char *client_id)
{
    _mqtt_client.loop();
    delay(10);
    if (!_mqtt_client.connected())
        connect(client_id);
}

String Subscriber::get_msg() { return _msg; }

String Subscriber::get_topic() { return _topic; }

void Subscriber::reset_msg()
{
    _msg = "";
    _topic = "";
}
```

### Sub.h
```cpp
#include <Arduino.h>
#include <MQTT.h>

class Subscriber
{
public:
    Subscriber(const char *mqtt_broker_ip, const int
                                               mqtt_broker_port);
    Subscriber(const char *mqtt_broker_ip, const int mqtt_broker_port, String *subscribe_topics, const int num_subscribe_topics);
    void connect(const char *client_id);
    void check_connection(const char *client_id);
    String get_msg();
    String get_topic();
    void reset_msg();

private:
    MQTTClient _mqtt_client;
    String *_subscribe_topics;
    int _num_subscribe_topics;
};
```

## Publisher 

### Pub.ino

```cpp
#include "Pub.h"
#include "WifiClient.h"

char *ssid_wifi = "ssid";
char *pass_wifi = "pass";

const char *mqtt_broker_ip = "172.20.10.2";
const int mqtt_broker_port = 1883;
const char *client_id = "pub";
const int num_subscribe_topics = 1;
String subscribe_topics[num_subscribe_topics] =
    {"toast"};
const char *publish_topic = "toast";
WifiClient wifi_client(ssid_wifi, pass_wifi);
Publisher publisher(mqtt_broker_ip, mqtt_broker_port,
                    subscribe_topics, num_subscribe_topics);

char *pub_mesg = "hello";
int i = 0;
int change = 0;

void setup()
{
    Serial.begin(9600);
    wifi_client.connect();
    publisher.connect(client_id);
}

void loop()
{
    if (change >= 5)
    {
        i++;
        pub_mesg[0] += i;
        change = 0;
    }
    publisher.check_connection(client_id);
    publisher.publish_message(publish_topic,
                              pub_mesg);
    change++;
    delay(1000);
}

```

### Pub.cpp

```cpp
#include "Pub.h"
#include <MQTT.h>
#include <ESP8266WiFi.h>

WiFiClient _wifi_client;
String _msg;
String _topic;
int _num_subscribe_topics;

Publisher::Publisher(const char *mqtt_broker_ip, const int mqtt_broker_port)
{
    _mqtt_client.begin(mqtt_broker_ip, _wifi_client);
}

Publisher::Publisher(const char *mqtt_broker_ip, const int mqtt_broker_port, String *subscribe_topics, const int num_subscribe_topics)
{
    _mqtt_client.begin(mqtt_broker_ip, _wifi_client);
    _subscribe_topics = subscribe_topics;
    _num_subscribe_topics = num_subscribe_topics;
}

void Publisher::connect(const char *client_id)
{
    Serial.print("Connecting to MQTT broker... ");
    while (!_mqtt_client.connect(client_id, "public",
                                 "public"))
    {
        Serial.print(".");
        delay(1000);
    }
    Serial.println("done!");
}

void Publisher::publish_message(const char *topic, const char *msg)
{
    _mqtt_client.publish(topic, msg);
    Serial.println("Message published [ " + String(topic) +
                   " ]: " + String(msg));
}

void Publisher::check_connection(const char *client_id)
{
    _mqtt_client.loop();
    delay(10);
    if (!_mqtt_client.connected())
        connect(client_id);
}

String Publisher::get_msg() { return _msg; }

String Publisher::get_topic() { return _topic; }

void Publisher::reset_msg()
{
    _msg = "";
    _topic = "";
}
```

### Pub.h
```cpp
#include <Arduino.h>
#include <MQTT.h>

class Publisher
{
public:
    Publisher(const char *mqtt_broker_ip, const int
                                               mqtt_broker_port);
    Publisher(const char *mqtt_broker_ip, const int mqtt_broker_port, String *subscribe_topics, const int num_subscribe_topics);
    void connect(const char *client_id);
    void publish_message(const char *topic, const char
                                                *msg);
    void check_connection(const char *client_id);
    String get_msg();
    String get_topic();
    void reset_msg();

private:
    MQTTClient _mqtt_client;
    String *_subscribe_topics;
    int _num_subscribe_topics;
};
```

## Outputs : 

### Publisher 
```
Message published [ toast ]: llo
Message published [ toast ]: llo
Message published [ toast ]: llo
Message published [ toast ]: llo
Message published [ toast ]: llo
Message published [ toast ]: 9ello
Message published [ toast ]: 9ello
Message published [ toast ]: 9ello
Message published [ toast ]: 9ello
Message published [ toast ]: 9ello
Message published [ toast ]: Xello
Message published [ toast ]: Xello
Message published [ toast ]: Xello
Message published [ toast ]: Xello
Message published [ toast ]: Xello
Message published [ toast ]: xello
Message published [ toast ]: xello
```

### Subscriber 

```
New Message arrived : llo
New Message arrived : 9ello
New Message arrived : Xello
New Message arrived : xello
```

# Assignment 3

```cpp
#include "MqttClient.h"
#include "WifiClient.h"
#include "DHT.h" // DHT module library
#include <ArduinoJson.h>

char *ssid_wifi = "ssid";
char *pass_wifi = "pass";

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
```


# Assignment 4

```cpp
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
```