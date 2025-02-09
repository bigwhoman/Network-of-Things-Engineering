#include "Sub.h"
#include "WifiClient.h"

char *ssid_wifi = "HIP";
char *pass_wifi = "bullshit1";

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
