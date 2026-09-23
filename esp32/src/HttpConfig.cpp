#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>

unsigned long measurementIdCounter = 0;
String getCurrentTime()
{
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo))
  {
    return "";
  }

  char timeString[25];
  strftime(timeString, sizeof(timeString),
  "%Y-%m-%dT%H:%M:%SZ", &timeinfo);

  return String(timeString);

}

String createMeasurement()
{
  JsonDocument doc;
  String time = getCurrentTime();
  String deviceId = "AE:12:03:88:94:33";
  if(time.isEmpty())
  {
    Serial.println("No time access");
    return "";
  }
  //measurementIdCounter++;
  //doc["measurementId"] = measurementIdCounter;
  doc["measurementType"] = "vibration";
  doc["measuredAtUTC"] = time;
  doc["deviceId"] = deviceId;
  doc["value"] = 1;
  doc["unit"] = "boolean";
  
  String json;
  serializeJson(doc,json);
  Serial.println("Timestamp: ");
  Serial.println(time);
  

  return json;
}

void sendMeasurement(String json)
{
  HTTPClient http;
  http.begin(
    "https://integration-service-gcayewebb3hjffb0.denmarkeast-01.azurewebsites.net/
    api/measurements/save");
  http.addHeader("Content-Type", "application/json");
  int responseCode = http.POST(json);
  Serial.println("HTTP Response: ");
  Serial.println(responseCode);

  http.end();
}