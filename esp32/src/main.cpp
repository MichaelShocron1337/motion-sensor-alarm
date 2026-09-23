#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <sensorConfig.h>
#include <httpConfig.h>
#include <connectionConfig.h>
#include <WiFiClientSecure.h>


void setup()
{
  activatePin();
  ConnectionControl();
  Serial.begin(115200);
}
void loop()
{
  motionDetected = false;
  if(motionDetected)
  {
    String currentMeasurement = createMeasurement();
    if(!currentMeasurement.isEmpty())
    {
      sendMeasurement(currentMeasurement);
    }
    Serial.println("Motion Detected!");
  }

}


