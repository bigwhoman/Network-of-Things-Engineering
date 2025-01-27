#include "WifiClient.h"

char *ssid = "HIP";
char *pass = "bullshit1";
WifiClient wifi_client(ssid, pass);

void setup()
{
  Serial.begin(9600);
  wifi_client.connect();
}

void loop()
{
  if (WiFi.status() != WL_CONNECTED){
    wifi_client.connect();
    while (WiFi.status() != WL_CONNECTED) {
       delay(500);
       Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address is: ");
    Serial.println(WiFi.localIP());
  }
}
