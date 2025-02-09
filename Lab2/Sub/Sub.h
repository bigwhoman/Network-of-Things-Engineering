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