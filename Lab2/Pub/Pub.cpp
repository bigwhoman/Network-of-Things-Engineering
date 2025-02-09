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