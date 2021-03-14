#include <RadioHead.h>

// Bibiotek som används samt hänvisningar till andra flikar här
#include <RH_ASK.h>
#include <SPI.h>
#include <ArduinoJson.h>
#include "functions.h"

#include <Esp32MQTTClient.h> 

// Text - Vilka kanaler på Esp32 som ska användas, här deklareras att jag ska använda 23 som receiver, 22 som transmitter
RH_ASK driver(2000, 23, 22, 0); // RH_ASK driver(2000, 11 reciver,12 transmitter, 0); 
              

char* ssid = "COMHEM_77cb2e"; // min WiFi uppkoppling och lösen
char* pass = "fjnwymyy";
// Text - Det unika DeviceId som hämtas från (Azure primarystring connection )
static char* connectionString = "HostName=IOT20-StudentAWHub.azure-devices.net;DeviceId=ESP32;SharedAccessKey=kgZu8XDjDv0KrV3WSDuDkcbE4hlK0CnuszPUi8ou+Kw="; 
static bool _connected = false; // en chechup för själva uppkopplingen
float temp = 0; // Sätter grundvärde 0 till temperature 


void setup() {
  
  // Startar upp med aktuell porthastighet ( 115200) med 2 sekunder delay efteråt, för att låta allt hinna med
  Serial.begin(115200);
  delay(2000); 

  // Hämtar information från funktions och iothub, och följer instruktionerna där 
  initWiFi(ssid, pass);
  initIotHub(); 
  driver.init(); // startkommando för RH_ASK
  
}

int count = 0; // måste deklarera countern till int och ett värde
void loop() {

  // storleksbestämmelse och typ av data på container buf
  uint8_t buf[64] = "\0";  
  uint8_t buflen = sizeof(buf); 

  // If sats där information om Driver funktionen för Esp32 och dess typ av data beskrivs och 
  
  if (driver.recv(buf, &buflen)) {
    
  // hanteras som ett Json meddelande, dvs görs om och definieras med namn doc och storlek 64
    DynamicJsonDocument doc(64);
    deserializeJson(doc, buf);

    // definierar det skickade meddelandet doc och återger varibabelnamnet temp där det faktiska värdet finns från sensorn,
    float temperature = doc["tmp"];  

    // Krav för sjäva värdeförändringen i en if-sats
    if (temperature < (temp - 0.2) || temperature > (temp  + 0.2)) {
      temp = temperature;
      // Om kravet ovan verkställs som skrivs det ut det aktuella temperaturen, definierad här som "temperature"
      Serial.println(temperature);

      // if-sats där om det är kopplat-utför följande
      if (_connected) {
      // typ bestämmelse och storlek
      char payload[64];
      // Använder Json typ på data, och det tilldelade variabel namn "payload"
      serializeJson(doc, payload);

      if(Esp32MQTTClient_SendEvent(payload)) { // If-sats där om esp32 sänder Jsonmeddelandet "payload"
        Serial.println(payload); // printa ut det som payload inehåller " datan - Temperatue"
        delay(1000); // fördöjning
        }
      }
    } 

    // om det inte sker en koppling/sändelse från esp32( i det här fallet den förändring i temeprature
    // då ska det printas ut texten " inget har förändrats"
    else {
      Serial.println("Inget har ändrats");
      
    }
    
  }
  
}
