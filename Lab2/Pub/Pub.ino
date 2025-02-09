#include "Pub.h"
#include "WifiClient.h"

char *ssid_wifi = "HIP";
char *pass_wifi = "bullshit1";

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
