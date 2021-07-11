#include <Arduino.h>

#include <env.h>
#include <screen.h>

#include <network.h>

#include <parser.h>
#include <pins.h>

#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>

Screen screen;
Network network;
Parser parser;

void setup()
{
  /*
  * Serial
  */
  Serial.begin(115200);

  /*
  * OLED
  */
  screen.setup();
  screen.drawImage();
  delay(3000);

  /*
  * Wifi Manager
  */
  String connecting = "Connecting...";
  screen.println(connecting);

  WiFiManager wifiManager;
  wifiManager.autoConnect("ISS Locator");
}

void loop()
{

  /*
  * Fetch ISS Data...
  */

  screen.drawImage();

  network.fetchISSLocation();
  delay(30000);
}
