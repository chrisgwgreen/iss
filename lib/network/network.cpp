#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <WiFiClientSecureBearSSL.h>

#include <env.h>
#include <network.h>
#include <parser.h>

Network::Network() {}

void Network::setup()
{
  Serial.print("Setting up NETWORK...");
  Serial.println("SUCCESS");
};

void Network::fetchISSLocation()
{

  WiFiClient client;

  HTTPClient http;

  Serial.print("[HTTP] begin...\n");
  if (http.begin(client, "http://api.open-notify.org/iss-now.json"))
  {

    Serial.print("[HTTP] GET...\n");
    int httpCode = http.GET();

    if (httpCode > 0)
    {
      Serial.printf("[HTTP] GET... code: %d\n", httpCode);

      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY)
      {

        /*
        * Parse ISS Location..
        */
        String payload = http.getString();
        parser.parseISSLocation(payload);
      }
    }
    else
    {
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
  }
  else
  {
    Serial.printf("[HTTP} Unable to connect\n");
  }
};

void Network::fetchGeocode(String lat, String lng)
{

  std::unique_ptr<BearSSL::WiFiClientSecure> client(new BearSSL::WiFiClientSecure);

  client->setInsecure();

  HTTPClient https;

  Serial.print("[HTTPS] Begin...\n");

  String geocode = "https://maps.googleapis.com/maps/api/geocode/json?latlng=" + lat + "," + lng + "&key=" + GEO_KEY;

  if (https.begin(*client, geocode))
  { // HTTPS

    int httpCode = https.GET();

    if (httpCode > 0)
    {

      Serial.printf("[HTTPS] GET... code: %d\n", httpCode);

      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY)
      {
        /*
        * Parse GEOCoder..
        */
        String payload = https.getString();
        parser.parseGEOCoder(lat, lng, payload);
      }
    }
    else
    {
      Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
    }

    https.end();
  }
  else
  {
    Serial.printf("[HTTPS] Unable to connect\n");
  }
}
