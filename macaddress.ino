#include <WiFi.h>
#include "time.h"
#include "Esp32MQTTClient.h"
#include "AzureIotHub.h"
#include <DHT.h>

#include <ArduinoJson.h>


#define INTERVAL 1000 * 5
#define DHT_PIN 23
#define DHT_TYPE DHT11

char *ssid = "wifi";
char *pass = "lösen";

char *conn = "HostName=IOT20-StudentAWHub.azure-devices.net;DeviceId=7c:9e:bd:f6:d3:dc;SharedAccessKey=QYByxLJDUws7++67olawEwyNX4A11EJSBxALbECpt4s=";

const char* ntpServer = "pool.ntp.org";
unsigned long epochTime;
//time_t epochTime;

bool messagePending = false;
unsigned long prevMillis = 0;
float prevTemperature = 0;

DHT dht(DHT_PIN, DHT_TYPE); 

//void getTime(){
    
unsigned long getTime() {
  time_t now;
  struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    return(0);
  }
  time(&now);
  return now;
}

void setup() {
  initSerial();
  initWifi();
  initDHT();
  //initTime();
  initDevice();
  configTime(0, 0, ntpServer);
  delay(2000);
 }   
   

void loop() {

  epochTime = getTime();
  Serial.print("Epoch Time: ");
  Serial.println(epochTime);
  delay(60 * 1000);
  //epochTime = time(NULL);
  
  unsigned long currentMillis = millis();
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  int timestamp = epochTime;
  

  if(!messagePending){
    if((currentMillis - prevMillis) > INTERVAL){
      prevMillis = currentMillis;

        if(!(std::isnan(temperature)) && !(std::isnan(humidity))){

          if((temperature + 1 > prevTemperature) || (temperature - 1 < prevTemperature)){
            prevTemperature = temperature;
          
            char payload[256];

            DynamicJsonDocument doc(1024);
            doc["temperature"] = temperature;
            doc["humidity"]   = humidity;
            doc["timestamp"] = timestamp;
            serializeJson(doc, payload);

            SendMessage(payload);
            Serial.println(epochTime);
          }
        }
      
    }
  }
  Esp32MQTTClient_Check(); 
  delay(10);
}
