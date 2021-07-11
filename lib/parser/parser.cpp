#include <Arduino.h>
#include <ArduinoJson.h>

#include <parser.h>
#include <network.h>
#include <screen.h>

Parser::Parser() {}

StaticJsonDocument<200> doc;

void Parser::parseISSLocation(String &line)
{

  DeserializationError error = deserializeJson(doc, line);

  if (error)
  {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }

  String latitude = doc["iss_position"]["latitude"];
  String longitude = doc["iss_position"]["longitude"];

  network.fetchGeocode(latitude, longitude);
};

void Parser::parseGEOCoder(String &lat, String &lng, String &line)
{

  int indexOfFormatted = line.indexOf("formatted_address");

  if (indexOfFormatted >= 0)
  {
    int indexOfEnd = line.indexOf("\n", indexOfFormatted);

    String location = line.substring(indexOfFormatted + 22, indexOfEnd - 2);
    screen.println(location);
  }
  else
  {
    String unknownLocation = "Unknown location";
    screen.println(unknownLocation);
  }
};
