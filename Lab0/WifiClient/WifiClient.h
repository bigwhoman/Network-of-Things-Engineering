#include <ESP8266WiFi.h>

class WifiClient
{
  public:
    WifiClient(char *ssid, char *pass);
    void connect();
    int wifiStatus;

  private:
    char *_ssid;
    char *_pass;
};
